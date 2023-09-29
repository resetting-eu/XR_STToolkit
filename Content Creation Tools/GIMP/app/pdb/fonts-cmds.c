/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
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

/* NOTE: This file is auto-generated by pdbgen.pl. */

#include "config.h"

#include "stamp-pdbgen.h"

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "core/gimp.h"
#include "core/gimpcontainer-filter.h"
#include "core/gimpcontainer.h"
#include "core/gimpdatafactory.h"
#include "core/gimpparamspecs.h"

#include "gimppdb.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
fonts_refresh_invoker (GimpProcedure         *procedure,
                       Gimp                  *gimp,
                       GimpContext           *context,
                       GimpProgress          *progress,
                       const GimpValueArray  *args,
                       GError               **error)
{
  gimp_data_factory_data_refresh (gimp->font_factory, context);
  gimp_data_factory_data_wait (gimp->font_factory);

  return gimp_procedure_get_return_values (procedure, TRUE, NULL);
}

static GimpValueArray *
fonts_get_list_invoker (GimpProcedure         *procedure,
                        Gimp                  *gimp,
                        GimpContext           *context,
                        GimpProgress          *progress,
                        const GimpValueArray  *args,
                        GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  const gchar *filter;
  gchar **font_list = NULL;

  filter = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      if (! gimp_data_factory_data_wait (gimp->font_factory))
        success = FALSE;

      if (success)
        {
          font_list = gimp_container_get_filtered_name_array (gimp_data_factory_get_container (gimp->font_factory),
                                                              filter);
        }
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    g_value_take_boxed (gimp_value_array_index (return_vals, 1), font_list);

  return return_vals;
}

void
register_fonts_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-fonts-refresh
   */
  procedure = gimp_procedure_new (fonts_refresh_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-fonts-refresh");
  gimp_procedure_set_static_help (procedure,
                                  "Refresh current fonts. This function always succeeds.",
                                  "This procedure retrieves all fonts currently in the user's font path and updates the font dialogs accordingly. Depending on the amount of fonts on the system, this can take considerable time.",
                                  NULL);
  gimp_procedure_set_static_attribution (procedure,
                                         "Sven Neumann <sven@gimp.org>",
                                         "Sven Neumann",
                                         "2003");
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-fonts-get-list
   */
  procedure = gimp_procedure_new (fonts_get_list_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-fonts-get-list");
  gimp_procedure_set_static_help (procedure,
                                  "Retrieve the list of loaded fonts.",
                                  "This procedure returns a list of the fonts that are currently available.",
                                  NULL);
  gimp_procedure_set_static_attribution (procedure,
                                         "Sven Neumann <sven@gimp.org>",
                                         "Sven Neumann",
                                         "2003");
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("filter",
                                                       "filter",
                                                       "An optional regular expression used to filter the list",
                                                       FALSE, TRUE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   g_param_spec_boxed ("font-list",
                                                       "font list",
                                                       "The list of font names",
                                                       G_TYPE_STRV,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}
