/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * shortcuts-rc.h
 * Copyright (C) 2023 Jehan
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

#ifndef __SHORTCUTS_RC_H__
#define __SHORTCUTS_RC_H__


gboolean   shortcuts_rc_parse (GtkApplication  *application,
                               GFile           *file,
                               GError         **error);
gboolean   shortcuts_rc_write (GtkApplication  *application,
                               GFile           *file,
                               GError         **error);


#endif /* __SHORTCUTS_RC_H__ */
