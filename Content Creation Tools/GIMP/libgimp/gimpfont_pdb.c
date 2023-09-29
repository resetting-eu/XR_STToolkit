/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpfont_pdb.c
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl */

#include "config.h"

#include "stamp-pdbgen.h"

#include "gimp.h"


/**
 * SECTION: gimpfont
 * @title: gimpfont
 * @short_description: Installable object used by text tools.
 *
 * Installable object used by text tools.
 **/


/**
 * gimp_font_get_by_name:
 * @name: The name of the font.
 *
 * Returns the font with the given name.
 *
 * Returns the font with the given name.
 *
 * Returns: (transfer none): The font.
 *
 * Since: 3.0
 **/
GimpFont *
gimp_font_get_by_name (const gchar *name)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpFont *font = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_STRING, name,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-font-get-by-name",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    font = GIMP_VALUES_GET_FONT (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return font;
}
