/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpdrawable_pdb.c
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
 * SECTION: gimpdrawable
 * @title: gimpdrawable
 * @short_description: Functions to manipulate drawables.
 *
 * Functions to manipulate drawables.
 **/


/**
 * _gimp_drawable_get_format:
 * @drawable: The drawable.
 *
 * Returns the drawable's Babl format
 *
 * This procedure returns the drawable's Babl format.
 * Note that the actual PDB procedure only transfers the format's
 * encoding. In order to get to the real format, the libbgimp C wrapper
 * must be used.
 *
 * Returns: (transfer full): The drawable's Babl format.
 *          The returned value must be freed with g_free().
 *
 * Since: 2.10
 **/
gchar *
_gimp_drawable_get_format (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gchar *format = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-get-format",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    format = GIMP_VALUES_DUP_STRING (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return format;
}

/**
 * _gimp_drawable_get_thumbnail_format:
 * @drawable: The drawable.
 *
 * Returns the drawable's thumbnail Babl format
 *
 * This procedure returns the drawable's thumbnail Babl format.
 * Thumbnails are always 8-bit images, see gimp_drawable_thumbnail()
 * and gimp_drawable_sub_thmbnail().
 *
 * Returns: (transfer full): The drawable's thumbnail Babl format.
 *          The returned value must be freed with g_free().
 *
 * Since: 2.10.14
 **/
gchar *
_gimp_drawable_get_thumbnail_format (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gchar *format = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-get-thumbnail-format",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    format = GIMP_VALUES_DUP_STRING (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return format;
}

/**
 * gimp_drawable_type:
 * @drawable: The drawable.
 *
 * Returns the drawable's type.
 *
 * This procedure returns the drawable's type.
 *
 * Returns: The drawable's type.
 **/
GimpImageType
gimp_drawable_type (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpImageType type = 0;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-type",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    type = GIMP_VALUES_GET_ENUM (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return type;
}

/**
 * gimp_drawable_type_with_alpha:
 * @drawable: The drawable.
 *
 * Returns the drawable's type with alpha.
 *
 * This procedure returns the drawable's type as if had an alpha
 * channel. If the type is currently Gray, for instance, the returned
 * type would be GrayA. If the drawable already has an alpha channel,
 * the drawable's type is simply returned.
 *
 * Returns: The drawable's type with alpha.
 **/
GimpImageType
gimp_drawable_type_with_alpha (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpImageType type_with_alpha = 0;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-type-with-alpha",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    type_with_alpha = GIMP_VALUES_GET_ENUM (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return type_with_alpha;
}

/**
 * gimp_drawable_has_alpha:
 * @drawable: The drawable.
 *
 * Returns TRUE if the drawable has an alpha channel.
 *
 * This procedure returns whether the specified drawable has an alpha
 * channel. This can only be true for layers, and the associated type
 * will be one of: { RGBA , GRAYA, INDEXEDA }.
 *
 * Returns: Does the drawable have an alpha channel?
 **/
gboolean
gimp_drawable_has_alpha (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean has_alpha = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-has-alpha",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    has_alpha = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return has_alpha;
}

/**
 * gimp_drawable_is_rgb:
 * @drawable: The drawable.
 *
 * Returns whether the drawable is an RGB type.
 *
 * This procedure returns TRUE if the specified drawable is of type {
 * RGB, RGBA }.
 *
 * Returns: TRUE if the drawable is an RGB type.
 **/
gboolean
gimp_drawable_is_rgb (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean is_rgb = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-is-rgb",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    is_rgb = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return is_rgb;
}

/**
 * gimp_drawable_is_gray:
 * @drawable: The drawable.
 *
 * Returns whether the drawable is a grayscale type.
 *
 * This procedure returns TRUE if the specified drawable is of type {
 * Gray, GrayA }.
 *
 * Returns: TRUE if the drawable is a grayscale type.
 **/
gboolean
gimp_drawable_is_gray (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean is_gray = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-is-gray",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    is_gray = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return is_gray;
}

/**
 * gimp_drawable_is_indexed:
 * @drawable: The drawable.
 *
 * Returns whether the drawable is an indexed type.
 *
 * This procedure returns TRUE if the specified drawable is of type {
 * Indexed, IndexedA }.
 *
 * Returns: TRUE if the drawable is an indexed type.
 **/
gboolean
gimp_drawable_is_indexed (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean is_indexed = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-is-indexed",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    is_indexed = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return is_indexed;
}

/**
 * gimp_drawable_get_bpp:
 * @drawable: The drawable.
 *
 * Returns the bytes per pixel.
 *
 * This procedure returns the number of bytes per pixel.
 *
 * Returns: Bytes per pixel.
 **/
gint
gimp_drawable_get_bpp (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gint bpp = 0;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-get-bpp",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    bpp = GIMP_VALUES_GET_INT (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return bpp;
}

/**
 * gimp_drawable_get_width:
 * @drawable: The drawable.
 *
 * Returns the width of the drawable.
 *
 * This procedure returns the specified drawable's width in pixels.
 *
 * Returns: Width of drawable.
 **/
gint
gimp_drawable_get_width (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gint width = 0;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-get-width",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    width = GIMP_VALUES_GET_INT (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return width;
}

/**
 * gimp_drawable_get_height:
 * @drawable: The drawable.
 *
 * Returns the height of the drawable.
 *
 * This procedure returns the specified drawable's height in pixels.
 *
 * Returns: Height of drawable.
 **/
gint
gimp_drawable_get_height (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gint height = 0;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-get-height",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    height = GIMP_VALUES_GET_INT (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return height;
}

/**
 * gimp_drawable_get_offsets:
 * @drawable: The drawable.
 * @offset_x: (out): x offset of drawable.
 * @offset_y: (out): y offset of drawable.
 *
 * Returns the offsets for the drawable.
 *
 * This procedure returns the specified drawable's offsets. This only
 * makes sense if the drawable is a layer since channels are anchored.
 * The offsets of a channel will be returned as 0.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_drawable_get_offsets (GimpDrawable *drawable,
                           gint         *offset_x,
                           gint         *offset_y)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-get-offsets",
                                              args);
  gimp_value_array_unref (args);

  *offset_x = 0;
  *offset_y = 0;

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  if (success)
    {
      *offset_x = GIMP_VALUES_GET_INT (return_vals, 1);
      *offset_y = GIMP_VALUES_GET_INT (return_vals, 2);
    }

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_drawable_mask_bounds:
 * @drawable: The drawable.
 * @x1: (out): x coordinate of the upper left corner of selection bounds.
 * @y1: (out): y coordinate of the upper left corner of selection bounds.
 * @x2: (out): x coordinate of the lower right corner of selection bounds.
 * @y2: (out): y coordinate of the lower right corner of selection bounds.
 *
 * Find the bounding box of the current selection in relation to the
 * specified drawable.
 *
 * This procedure returns whether there is a selection. If there is
 * one, the upper left and lower right-hand corners of its bounding box
 * are returned. These coordinates are specified relative to the
 * drawable's origin, and bounded by the drawable's extents. Please
 * note that the pixel specified by the lower right-hand coordinate of
 * the bounding box is not part of the selection. The selection ends at
 * the upper left corner of this pixel. This means the width of the
 * selection can be calculated as (x2 - x1), its height as (y2 - y1).
 * Note that the returned boolean does NOT correspond with the returned
 * region being empty or not, it always returns whether the selection
 * is non_empty. See gimp_drawable_mask_intersect() for a boolean
 * return value which is more useful in most cases.
 *
 * Returns: TRUE if there is a selection.
 **/
gboolean
gimp_drawable_mask_bounds (GimpDrawable *drawable,
                           gint         *x1,
                           gint         *y1,
                           gint         *x2,
                           gint         *y2)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean non_empty = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-mask-bounds",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    {
      non_empty = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);
      *x1 = GIMP_VALUES_GET_INT (return_vals, 2);
      *y1 = GIMP_VALUES_GET_INT (return_vals, 3);
      *x2 = GIMP_VALUES_GET_INT (return_vals, 4);
      *y2 = GIMP_VALUES_GET_INT (return_vals, 5);
    }

  gimp_value_array_unref (return_vals);

  return non_empty;
}

/**
 * gimp_drawable_mask_intersect:
 * @drawable: The drawable.
 * @x: (out): x coordinate of the upper left corner of the intersection.
 * @y: (out): y coordinate of the upper left corner of the intersection.
 * @width: (out): width of the intersection.
 * @height: (out): height of the intersection.
 *
 * Find the bounding box of the current selection in relation to the
 * specified drawable.
 *
 * This procedure returns whether there is an intersection between the
 * drawable and the selection. Unlike gimp_drawable_mask_bounds(), the
 * intersection's bounds are returned as x, y, width, height.
 * If there is no selection this function returns TRUE and the returned
 * bounds are the extents of the whole drawable.
 *
 * Returns: TRUE if the returned area is not empty.
 *
 * Since: 2.2
 **/
gboolean
gimp_drawable_mask_intersect (GimpDrawable *drawable,
                              gint         *x,
                              gint         *y,
                              gint         *width,
                              gint         *height)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean non_empty = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-mask-intersect",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    {
      non_empty = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);
      *x = GIMP_VALUES_GET_INT (return_vals, 2);
      *y = GIMP_VALUES_GET_INT (return_vals, 3);
      *width = GIMP_VALUES_GET_INT (return_vals, 4);
      *height = GIMP_VALUES_GET_INT (return_vals, 5);
    }

  gimp_value_array_unref (return_vals);

  return non_empty;
}

/**
 * gimp_drawable_merge_shadow:
 * @drawable: The drawable.
 * @undo: Push merge to undo stack?
 *
 * Merge the shadow buffer with the specified drawable.
 *
 * This procedure combines the contents of the drawable's shadow buffer
 * (for temporary processing) with the specified drawable. The 'undo'
 * parameter specifies whether to add an undo step for the operation.
 * Requesting no undo is useful for such applications as 'auto-apply'.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_drawable_merge_shadow (GimpDrawable *drawable,
                            gboolean      undo)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_BOOLEAN, undo,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-merge-shadow",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_drawable_free_shadow:
 * @drawable: The drawable.
 *
 * Free the specified drawable's shadow data (if it exists).
 *
 * This procedure is intended as a memory saving device. If any shadow
 * memory has been allocated, it will be freed automatically when the
 * drawable is removed from the image, or when the plug-in procedure
 * which allocated it returns.
 *
 * Returns: TRUE on success.
 *
 * Since: 2.6
 **/
gboolean
gimp_drawable_free_shadow (GimpDrawable *drawable)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-free-shadow",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_drawable_update:
 * @drawable: The drawable.
 * @x: x coordinate of upper left corner of update region.
 * @y: y coordinate of upper left corner of update region.
 * @width: Width of update region.
 * @height: Height of update region.
 *
 * Update the specified region of the drawable.
 *
 * This procedure updates the specified region of the drawable. The (x,
 * y) coordinate pair is relative to the drawable's origin, not to the
 * image origin. Therefore, the entire drawable can be updated using
 * (0, 0, width, height).
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_drawable_update (GimpDrawable *drawable,
                      gint          x,
                      gint          y,
                      gint          width,
                      gint          height)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_INT, x,
                                          G_TYPE_INT, y,
                                          G_TYPE_INT, width,
                                          G_TYPE_INT, height,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-update",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_drawable_fill:
 * @drawable: The drawable.
 * @fill_type: The type of fill.
 *
 * Fill the drawable with the specified fill mode.
 *
 * This procedure fills the drawable. If the fill mode is foreground
 * the current foreground color is used. If the fill mode is
 * background, the current background color is used. If the fill type
 * is white, then white is used. Transparent fill only affects layers
 * with an alpha channel, in which case the alpha channel is set to
 * transparent. If the drawable has no alpha channel, it is filled to
 * white. No fill leaves the drawable's contents undefined.
 * This procedure is unlike gimp_drawable_edit_fill() or the bucket
 * fill tool because it fills regardless of a selection. Its main
 * purpose is to fill a newly created drawable before adding it to the
 * image. This operation cannot be undone.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_drawable_fill (GimpDrawable *drawable,
                    GimpFillType  fill_type)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          GIMP_TYPE_FILL_TYPE, fill_type,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-fill",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_drawable_offset:
 * @drawable: The drawable to offset.
 * @wrap_around: wrap image around or fill vacated regions.
 * @fill_type: fill vacated regions of drawable with background or transparent.
 * @offset_x: offset by this amount in X direction.
 * @offset_y: offset by this amount in Y direction.
 *
 * Offset the drawable by the specified amounts in the X and Y
 * directions
 *
 * This procedure offsets the specified drawable by the amounts
 * specified by 'offset_x' and 'offset_y'. If 'wrap_around' is set to
 * TRUE, then portions of the drawable which are offset out of bounds
 * are wrapped around. Alternatively, the undefined regions of the
 * drawable can be filled with transparency or the background color, as
 * specified by the 'fill-type' parameter.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_drawable_offset (GimpDrawable   *drawable,
                      gboolean        wrap_around,
                      GimpOffsetType  fill_type,
                      gint            offset_x,
                      gint            offset_y)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_BOOLEAN, wrap_around,
                                          GIMP_TYPE_OFFSET_TYPE, fill_type,
                                          G_TYPE_INT, offset_x,
                                          G_TYPE_INT, offset_y,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-offset",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * _gimp_drawable_thumbnail:
 * @drawable: The drawable.
 * @width: The requested thumbnail width.
 * @height: The requested thumbnail height.
 * @actual_width: (out): The previews width.
 * @actual_height: (out): The previews height.
 * @bpp: (out): The previews bpp.
 * @thumbnail_data: (out) (transfer full): The thumbnail data.
 *
 * Get a thumbnail of a drawable.
 *
 * This function gets data from which a thumbnail of a drawable preview
 * can be created. Maximum x or y dimension is 1024 pixels. The pixels
 * are returned in RGB[A] or GRAY[A] format. The bpp return value gives
 * the number of bytes in the image.
 *
 * Returns: TRUE on success.
 **/
gboolean
_gimp_drawable_thumbnail (GimpDrawable  *drawable,
                          gint           width,
                          gint           height,
                          gint          *actual_width,
                          gint          *actual_height,
                          gint          *bpp,
                          GBytes       **thumbnail_data)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_INT, width,
                                          G_TYPE_INT, height,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-thumbnail",
                                              args);
  gimp_value_array_unref (args);

  *actual_width = 0;
  *actual_height = 0;
  *bpp = 0;
  *thumbnail_data = NULL;

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  if (success)
    {
      *actual_width = GIMP_VALUES_GET_INT (return_vals, 1);
      *actual_height = GIMP_VALUES_GET_INT (return_vals, 2);
      *bpp = GIMP_VALUES_GET_INT (return_vals, 3);
      *thumbnail_data = GIMP_VALUES_DUP_BYTES (return_vals, 4);
    }

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * _gimp_drawable_sub_thumbnail:
 * @drawable: The drawable.
 * @src_x: The x coordinate of the area.
 * @src_y: The y coordinate of the area.
 * @src_width: The width of the area.
 * @src_height: The height of the area.
 * @dest_width: The thumbnail width.
 * @dest_height: The thumbnail height.
 * @width: (out): The previews width.
 * @height: (out): The previews height.
 * @bpp: (out): The previews bpp.
 * @thumbnail_data: (out) (transfer full): The thumbnail data.
 *
 * Get a thumbnail of a sub-area of a drawable drawable.
 *
 * This function gets data from which a thumbnail of a drawable preview
 * can be created. Maximum x or y dimension is 1024 pixels. The pixels
 * are returned in RGB[A] or GRAY[A] format. The bpp return value gives
 * the number of bytes in the image.
 *
 * Returns: TRUE on success.
 *
 * Since: 2.2
 **/
gboolean
_gimp_drawable_sub_thumbnail (GimpDrawable  *drawable,
                              gint           src_x,
                              gint           src_y,
                              gint           src_width,
                              gint           src_height,
                              gint           dest_width,
                              gint           dest_height,
                              gint          *width,
                              gint          *height,
                              gint          *bpp,
                              GBytes       **thumbnail_data)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          G_TYPE_INT, src_x,
                                          G_TYPE_INT, src_y,
                                          G_TYPE_INT, src_width,
                                          G_TYPE_INT, src_height,
                                          G_TYPE_INT, dest_width,
                                          G_TYPE_INT, dest_height,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-sub-thumbnail",
                                              args);
  gimp_value_array_unref (args);

  *width = 0;
  *height = 0;
  *bpp = 0;
  *thumbnail_data = NULL;

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  if (success)
    {
      *width = GIMP_VALUES_GET_INT (return_vals, 1);
      *height = GIMP_VALUES_GET_INT (return_vals, 2);
      *bpp = GIMP_VALUES_GET_INT (return_vals, 3);
      *thumbnail_data = GIMP_VALUES_DUP_BYTES (return_vals, 4);
    }

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_drawable_foreground_extract:
 * @drawable: The drawable.
 * @mode: The algorithm to use.
 * @mask: Tri-Map.
 *
 * Extract the foreground of a drawable using a given trimap.
 *
 * Image Segmentation by Uniform Color Clustering, see
 * https://www.inf.fu-berlin.de/inst/pubs/tr-b-05-07.pdf
 *
 * Returns: TRUE on success.
 *
 * Since: 2.4
 **/
gboolean
gimp_drawable_foreground_extract (GimpDrawable              *drawable,
                                  GimpForegroundExtractMode  mode,
                                  GimpDrawable              *mask)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_DRAWABLE, drawable,
                                          GIMP_TYPE_FOREGROUND_EXTRACT_MODE, mode,
                                          GIMP_TYPE_DRAWABLE, mask,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-drawable-foreground-extract",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}
