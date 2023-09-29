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

#ifndef __SCHEME_MARSHAL_H__
#define __SCHEME_MARSHAL_H__

pointer       get_drawable_from_script         (scheme        *sc,
                                                pointer        a,
                                                gint           id,
                                                GimpDrawable **drawable_handle);

pointer       marshal_ID_to_drawable           (scheme   *sc,
                                                pointer   a,
                                                gint      id,
                                                GValue   *value);

pointer       marshal_vector_to_drawable_array (scheme   *sc,
                                                pointer   a,
                                                GValue   *value);

void          marshal_path_string_to_gfile     (scheme   *sc,
                                                pointer   a,
                                                GValue   *value);


pointer       marshal_returned_object_array_to_vector (scheme   *sc,
                                                       GValue   *value);

gchar *       marshal_returned_gfile_to_string        (GValue   *value);

#endif /* __SCHEME_MARSHAL_H__ */
