/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimageselect_pdb.c
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
 * SECTION: gimpimageselect
 * @title: gimpimageselect
 * @short_description: Modify the image's selection.
 *
 * Functions to modify the image's selection.
 **/


/**
 * gimp_image_select_color:
 * @image: The affected image.
 * @operation: The selection operation.
 * @drawable: The affected drawable.
 * @color: The color to select.
 *
 * Create a selection by selecting all pixels (in the specified
 * drawable) with the same (or similar) color to that specified.
 *
 * This tool creates a selection over the specified image. A by-color
 * selection is determined by the supplied color under the constraints
 * of the current context settings. Essentially, all pixels (in the
 * drawable) that have color sufficiently close to the specified color
 * (as determined by the threshold and criterion context values) are
 * included in the selection. To select transparent regions, the color
 * specified must also have minimum alpha.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius(), gimp_context_set_sample_merged(),
 * gimp_context_set_sample_criterion(),
 * gimp_context_set_sample_threshold(),
 * gimp_context_set_sample_transparent().
 *
 * In the case of a merged sampling, the supplied drawable is ignored.
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_color (GimpImage      *image,
                         GimpChannelOps  operation,
                         GimpDrawable   *drawable,
                         const GimpRGB  *color)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          GIMP_TYPE_RGB, color,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-color",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_image_select_contiguous_color:
 * @image: The affected image.
 * @operation: The selection operation.
 * @drawable: The affected drawable.
 * @x: x coordinate of initial seed fill point: (image coordinates).
 * @y: y coordinate of initial seed fill point: (image coordinates).
 *
 * Create a selection by selecting all pixels around specified
 * coordinates with the same (or similar) color to that at the
 * coordinates.
 *
 * This tool creates a contiguous selection over the specified image. A
 * contiguous color selection is determined by a seed fill under the
 * constraints of the current context settings. Essentially, the color
 * at the specified coordinates (in the drawable) is measured and the
 * selection expands outwards from that point to any adjacent pixels
 * which are not significantly different (as determined by the
 * threshold and criterion context settings). This process continues
 * until no more expansion is possible. If antialiasing is turned on,
 * the final selection mask will contain intermediate values based on
 * close misses to the threshold bar at pixels along the seed fill
 * boundary.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius(), gimp_context_set_sample_merged(),
 * gimp_context_set_sample_criterion(),
 * gimp_context_set_sample_threshold(),
 * gimp_context_set_sample_transparent(),
 * gimp_context_set_diagonal_neighbors().
 *
 * In the case of a merged sampling, the supplied drawable is ignored.
 * If the sample is merged, the specified coordinates are relative to
 * the image origin; otherwise, they are relative to the drawable's
 * origin.
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_contiguous_color (GimpImage      *image,
                                    GimpChannelOps  operation,
                                    GimpDrawable   *drawable,
                                    gdouble         x,
                                    gdouble         y)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_DOUBLE, x,
                                          G_TYPE_DOUBLE, y,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-contiguous-color",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_image_select_rectangle:
 * @image: The image.
 * @operation: The selection operation.
 * @x: x coordinate of upper-left corner of rectangle.
 * @y: y coordinate of upper-left corner of rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 *
 * Create a rectangular selection over the specified image;
 *
 * This tool creates a rectangular selection over the specified image.
 * The rectangular region can be either added to, subtracted from, or
 * replace the contents of the previous selection mask.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_feather(), gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_rectangle (GimpImage      *image,
                             GimpChannelOps  operation,
                             gdouble         x,
                             gdouble         y,
                             gdouble         width,
                             gdouble         height)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          G_TYPE_DOUBLE, x,
                                          G_TYPE_DOUBLE, y,
                                          G_TYPE_DOUBLE, width,
                                          G_TYPE_DOUBLE, height,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-rectangle",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_image_select_round_rectangle:
 * @image: The image.
 * @operation: The selection operation.
 * @x: x coordinate of upper-left corner of rectangle.
 * @y: y coordinate of upper-left corner of rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 * @corner_radius_x: The corner radius in X direction.
 * @corner_radius_y: The corner radius in Y direction.
 *
 * Create a rectangular selection with round corners over the specified
 * image;
 *
 * This tool creates a rectangular selection with round corners over
 * the specified image. The rectangular region can be either added to,
 * subtracted from, or replace the contents of the previous selection
 * mask.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_round_rectangle (GimpImage      *image,
                                   GimpChannelOps  operation,
                                   gdouble         x,
                                   gdouble         y,
                                   gdouble         width,
                                   gdouble         height,
                                   gdouble         corner_radius_x,
                                   gdouble         corner_radius_y)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          G_TYPE_DOUBLE, x,
                                          G_TYPE_DOUBLE, y,
                                          G_TYPE_DOUBLE, width,
                                          G_TYPE_DOUBLE, height,
                                          G_TYPE_DOUBLE, corner_radius_x,
                                          G_TYPE_DOUBLE, corner_radius_y,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-round-rectangle",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_image_select_ellipse:
 * @image: The image.
 * @operation: The selection operation.
 * @x: x coordinate of upper-left corner of ellipse bounding box.
 * @y: y coordinate of upper-left corner of ellipse bounding box.
 * @width: The width of the ellipse.
 * @height: The height of the ellipse.
 *
 * Create an elliptical selection over the specified image.
 *
 * This tool creates an elliptical selection over the specified image.
 * The elliptical region can be either added to, subtracted from, or
 * replace the contents of the previous selection mask.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_ellipse (GimpImage      *image,
                           GimpChannelOps  operation,
                           gdouble         x,
                           gdouble         y,
                           gdouble         width,
                           gdouble         height)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          G_TYPE_DOUBLE, x,
                                          G_TYPE_DOUBLE, y,
                                          G_TYPE_DOUBLE, width,
                                          G_TYPE_DOUBLE, height,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-ellipse",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_image_select_polygon:
 * @image: The image.
 * @operation: The selection operation.
 * @num_segs: Number of points (count 1 coordinate as two points).
 * @segs: (array length=num_segs) (element-type gdouble): Array of points: { p1.x, p1.y, p2.x, p2.y, ..., pn.x, pn.y}.
 *
 * Create a polygonal selection over the specified image.
 *
 * This tool creates a polygonal selection over the specified image.
 * The polygonal region can be either added to, subtracted from, or
 * replace the contents of the previous selection mask. The polygon is
 * specified through an array of floating point numbers and its length.
 * The length of array must be 2n, where n is the number of points.
 * Each point is defined by 2 floating point values which correspond to
 * the x and y coordinates. If the final point does not connect to the
 * starting point, a connecting segment is automatically added.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_polygon (GimpImage      *image,
                           GimpChannelOps  operation,
                           gint            num_segs,
                           const gdouble  *segs)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          G_TYPE_INT, num_segs,
                                          GIMP_TYPE_FLOAT_ARRAY, NULL,
                                          G_TYPE_NONE);
  gimp_value_set_float_array (gimp_value_array_index (args, 3), segs, num_segs);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-polygon",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_image_select_item:
 * @image: The image.
 * @operation: The desired operation with current selection.
 * @item: The item to render to the selection.
 *
 * Transforms the specified item into a selection
 *
 * This procedure renders the item's outline into the current selection
 * of the image the item belongs to. What exactly the item's outline is
 * depends on the item type: for layers, it's the layer's alpha
 * channel, for vectors the vector's shape.
 *
 * This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: 2.8
 **/
gboolean
gimp_image_select_item (GimpImage      *image,
                        GimpChannelOps  operation,
                        GimpItem       *item)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          GIMP_TYPE_CHANNEL_OPS, operation,
                                          GIMP_TYPE_ITEM, item,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-image-select-item",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}
