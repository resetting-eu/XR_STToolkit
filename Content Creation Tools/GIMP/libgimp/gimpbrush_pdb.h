/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpbrush_pdb.h
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

#if !defined (__GIMP_H_INSIDE__) && !defined (GIMP_COMPILATION)
#error "Only <libgimp/gimp.h> can be included directly."
#endif

#ifndef __GIMP_BRUSH_PDB_H__
#define __GIMP_BRUSH_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


GimpBrush* gimp_brush_new              (const gchar              *name);
GimpBrush* gimp_brush_get_by_name      (const gchar              *name);
gboolean   gimp_brush_is_generated     (GimpBrush                *brush);
gboolean   gimp_brush_get_info         (GimpBrush                *brush,
                                        gint                     *width,
                                        gint                     *height,
                                        gint                     *mask_bpp,
                                        gint                     *color_bpp);
gboolean   gimp_brush_get_pixels       (GimpBrush                *brush,
                                        gint                     *width,
                                        gint                     *height,
                                        gint                     *mask_bpp,
                                        GBytes                  **mask_bytes,
                                        gint                     *color_bpp,
                                        GBytes                  **color_bytes);
gint       gimp_brush_get_spacing      (GimpBrush                *brush);
gboolean   gimp_brush_set_spacing      (GimpBrush                *brush,
                                        gint                      spacing);
gboolean   gimp_brush_get_shape        (GimpBrush                *brush,
                                        GimpBrushGeneratedShape  *shape);
gboolean   gimp_brush_set_shape        (GimpBrush                *brush,
                                        GimpBrushGeneratedShape   shape_in,
                                        GimpBrushGeneratedShape  *shape_out);
gboolean   gimp_brush_get_radius       (GimpBrush                *brush,
                                        gdouble                  *radius);
gboolean   gimp_brush_set_radius       (GimpBrush                *brush,
                                        gdouble                   radius_in,
                                        gdouble                  *radius_out);
gboolean   gimp_brush_get_spikes       (GimpBrush                *brush,
                                        gint                     *spikes);
gboolean   gimp_brush_set_spikes       (GimpBrush                *brush,
                                        gint                      spikes_in,
                                        gint                     *spikes_out);
gboolean   gimp_brush_get_hardness     (GimpBrush                *brush,
                                        gdouble                  *hardness);
gboolean   gimp_brush_set_hardness     (GimpBrush                *brush,
                                        gdouble                   hardness_in,
                                        gdouble                  *hardness_out);
gboolean   gimp_brush_get_aspect_ratio (GimpBrush                *brush,
                                        gdouble                  *aspect_ratio);
gboolean   gimp_brush_set_aspect_ratio (GimpBrush                *brush,
                                        gdouble                   aspect_ratio_in,
                                        gdouble                  *aspect_ratio_out);
gboolean   gimp_brush_get_angle        (GimpBrush                *brush,
                                        gdouble                  *angle);
gboolean   gimp_brush_set_angle        (GimpBrush                *brush,
                                        gdouble                   angle_in,
                                        gdouble                  *angle_out);


G_END_DECLS

#endif /* __GIMP_BRUSH_PDB_H__ */