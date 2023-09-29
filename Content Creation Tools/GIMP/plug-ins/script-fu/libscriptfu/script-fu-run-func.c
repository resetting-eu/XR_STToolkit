/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <string.h>
#include <glib.h>

#include <libgimp/gimp.h>

#include "scheme-wrapper.h"       /* type "pointer" */

#include "script-fu-types.h"
#include "script-fu-interface.h"  /* ScriptFu's GUI implementation. */
#include "script-fu-dialog.h"     /* Gimp's GUI implementation. */
#include "script-fu-script.h"
#include "script-fu-scripts.h"    /* script_fu_find_script */
#include "script-fu-command.h"

#include "script-fu-run-func.h"

/* Outer run_funcs
 * One each for GimpProcedure and GimpImageProcedure.
 * These are called from Gimp, with two different signatures.
 * These form and interpret "commands" which are calls to inner run_funcs
 * defined in Scheme by a script.

 * These return the result of interpretation,
 * in a GimpValueArray whose only element is a status.
 * !!! ScriptFu does not let authors define procedures that return values.
 */

/* run_func for a GimpImageProcedure
 *
 * Type is GimpRunImageFunc.
 *
 * Uses Gimp's config and gui.
 *
 * Since 3.0
 */
GimpValueArray *
script_fu_run_image_procedure ( GimpProcedure         *procedure, /* GimpImageProcedure */
                                GimpRunMode           run_mode,
                                GimpImage            *image,
                                guint                 n_drawables,
                                GimpDrawable        **drawables,
                                const GimpValueArray *other_args,
                                gpointer              data)
{

  GimpValueArray    *result = NULL;
  SFScript          *script;

  g_debug ("script_fu_run_image_procedure");
  script = script_fu_find_script (gimp_procedure_get_name (procedure));

  if (! script)
    return gimp_procedure_new_return_values (procedure, GIMP_PDB_CALLING_ERROR, NULL);

  ts_set_run_mode (run_mode);

  switch (run_mode)
    {
    case GIMP_RUN_INTERACTIVE:
      {
        if (gimp_value_array_length (other_args) > 0)
          {
            /* Let user choose "other" args in a dialog, then interpret. Maintain a config. */
            result = script_fu_dialog_run (procedure, script, image, n_drawables, drawables, other_args);
          }
        else
          {
            /* No "other" args for user to choose. No config to maintain. */
            result = script_fu_interpret_image_proc (procedure, script, image, n_drawables, drawables, other_args);
          }
        break;
      }
    case GIMP_RUN_NONINTERACTIVE:
      {
        /* A call from another PDB procedure.
         * Use the given other_args, without interacting with user.
         * Since no user interaction, no config to maintain.
         */
        result = script_fu_interpret_image_proc (procedure, script, image, n_drawables, drawables, other_args);
        break;
      }
    case GIMP_RUN_WITH_LAST_VALS:
      {
        /* User invoked from a menu "Filter>Run with last values".
         * Do not show dialog. other_args are already last values, from a config.
         */
        result = script_fu_interpret_image_proc (procedure, script, image, n_drawables, drawables, other_args);
        break;
      }
    default:
      {
        result = gimp_procedure_new_return_values (procedure, GIMP_PDB_CALLING_ERROR, NULL);
      }
    }
  return result;
}


/* run_func for a GimpProcedure.
 *
 * Type is GimpRunFunc
 *
 * Uses ScriptFu's own GUI implementation, and retains settings locally.
 *
 * Since prior to 3.0 but formerly named script_fu_script_proc
 */
GimpValueArray *
script_fu_run_procedure (GimpProcedure        *procedure,
                         const GimpValueArray *args,
                         gpointer              data)
{
  GimpPDBStatusType  status = GIMP_PDB_SUCCESS;
  SFScript          *script;
  GimpRunMode        run_mode;
  GError            *error = NULL;

  script = script_fu_find_script (gimp_procedure_get_name (procedure));

  if (! script)
    return gimp_procedure_new_return_values (procedure,
                                             GIMP_PDB_CALLING_ERROR,
                                             NULL);

  run_mode = GIMP_VALUES_GET_ENUM (args, 0);

  ts_set_run_mode (run_mode);

  switch (run_mode)
    {
    case GIMP_RUN_INTERACTIVE:
      {
        gint min_args = 0;

        /*  First, try to collect the standard script arguments...  */
        min_args = script_fu_script_collect_standard_args (script, args);

        /*  ...then acquire the rest of arguments (if any) with a dialog  */
        if (script->n_args > min_args)
          {
            status = script_fu_interface (script, min_args);
            break;
          }
        /*  otherwise (if the script takes no more arguments), skip
         *  this part and run the script directly (fallthrough)
         */
      }

    case GIMP_RUN_NONINTERACTIVE:
      /*  Make sure all the arguments are there  */
      if (gimp_value_array_length (args) != (script->n_args + 1))
        status = GIMP_PDB_CALLING_ERROR;

      if (status == GIMP_PDB_SUCCESS)
        {
          gchar *command;

          command = script_fu_script_get_command_from_params (script, args);

          /*  run the command through the interpreter  */
          if (! script_fu_run_command (command, &error))
            {
              return gimp_procedure_new_return_values (procedure,
                                                       GIMP_PDB_EXECUTION_ERROR,
                                                       error);
            }

          g_free (command);
        }
      break;

    case GIMP_RUN_WITH_LAST_VALS:
      {
        gchar *command;

        /*  First, try to collect the standard script arguments  */
        script_fu_script_collect_standard_args (script, args);

        command = script_fu_script_get_command (script);

        /*  run the command through the interpreter  */
        if (! script_fu_run_command (command, &error))
          {
            return gimp_procedure_new_return_values (procedure,
                                                     GIMP_PDB_EXECUTION_ERROR,
                                                     error);
          }

        g_free (command);
      }
      break;

    default:
      break;
    }

  return gimp_procedure_new_return_values (procedure, status, NULL);
}
