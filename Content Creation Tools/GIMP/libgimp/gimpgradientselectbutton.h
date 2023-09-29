/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * gimpgradientselectbutton.h
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

#if !defined (__GIMP_UI_H_INSIDE__) && !defined (GIMP_COMPILATION)
#error "Only <libgimp/gimpui.h> can be included directly."
#endif

#ifndef __GIMP_GRADIENT_SELECT_BUTTON_H__
#define __GIMP_GRADIENT_SELECT_BUTTON_H__

#include <libgimp/gimpresourceselectbutton.h>

G_BEGIN_DECLS

#define GIMP_TYPE_GRADIENT_SELECT_BUTTON (gimp_gradient_select_button_get_type ())
G_DECLARE_FINAL_TYPE (GimpGradientSelectButton,
                      gimp_gradient_select_button,
                      GIMP,
                      GRADIENT_SELECT_BUTTON,
                      GimpResourceSelectButton)


GtkWidget * gimp_gradient_select_button_new (const gchar  *title,
                                             GimpResource *gradient);


G_END_DECLS

#endif /* __GIMP_GRADIENT_SELECT_BUTTON_H__ */
