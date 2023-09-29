/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpfile_pdb.c
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
 * SECTION: gimpfile
 * @title: gimpfile
 * @short_description: Image file operations (load, save, etc.)
 *
 * Image file operations (load, save, etc.)
 **/


/**
 * gimp_file_load:
 * @run_mode: The run mode.
 * @file: The file to load.
 *
 * Loads an image file by invoking the right load handler.
 *
 * This procedure invokes the correct file load handler using magic if
 * possible, and falling back on the file's extension and/or prefix if
 * not.
 *
 * Returns: (transfer none): The output image.
 **/
GimpImage *
gimp_file_load (GimpRunMode  run_mode,
                GFile       *file)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpImage *image = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RUN_MODE, run_mode,
                                          G_TYPE_FILE, file,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-file-load",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    image = GIMP_VALUES_GET_IMAGE (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return image;
}

/**
 * gimp_file_load_layer:
 * @run_mode: The run mode.
 * @image: Destination image.
 * @file: The file to load.
 *
 * Loads an image file as a layer for an existing image.
 *
 * This procedure behaves like the file-load procedure but opens the
 * specified image as a layer for an existing image. The returned layer
 * needs to be added to the existing image with
 * gimp_image_insert_layer().
 *
 * Returns: (transfer none): The layer created when loading the image file.
 *
 * Since: 2.4
 **/
GimpLayer *
gimp_file_load_layer (GimpRunMode  run_mode,
                      GimpImage   *image,
                      GFile       *file)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpLayer *layer = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RUN_MODE, run_mode,
                                          GIMP_TYPE_IMAGE, image,
                                          G_TYPE_FILE, file,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-file-load-layer",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    layer = GIMP_VALUES_GET_LAYER (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return layer;
}

/**
 * gimp_file_load_layers:
 * @run_mode: The run mode.
 * @image: Destination image.
 * @file: The file to load.
 * @num_layers: (out): The number of loaded layers.
 *
 * Loads an image file as layers for an existing image.
 *
 * This procedure behaves like the file-load procedure but opens the
 * specified image as layers for an existing image. The returned layers
 * needs to be added to the existing image with
 * gimp_image_insert_layer().
 *
 * Returns: (array length=num_layers) (element-type GimpLayer) (transfer container):
 *          The list of loaded layers.
 *          The returned value must be freed with g_free().
 *
 * Since: 2.4
 **/
GimpLayer **
gimp_file_load_layers (GimpRunMode  run_mode,
                       GimpImage   *image,
                       GFile       *file,
                       gint        *num_layers)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpLayer **layers = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RUN_MODE, run_mode,
                                          GIMP_TYPE_IMAGE, image,
                                          G_TYPE_FILE, file,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-file-load-layers",
                                              args);
  gimp_value_array_unref (args);

  *num_layers = 0;

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    {
      *num_layers = GIMP_VALUES_GET_INT (return_vals, 1);
      { GimpObjectArray *a = g_value_get_boxed (gimp_value_array_index (return_vals, 2)); if (a) layers = g_memdup2 (a->data, a->length * sizeof (gpointer)); };
    }

  gimp_value_array_unref (return_vals);

  return layers;
}

/**
 * gimp_file_save:
 * @run_mode: The run mode.
 * @image: Input image.
 * @num_drawables: The number of drawables to save.
 * @drawables: (array length=num_drawables) (element-type GimpItem): Drawables to save.
 * @file: The file to save the image in.
 *
 * Saves a file by extension.
 *
 * This procedure invokes the correct file save handler according to
 * the file's extension and/or prefix.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_file_save (GimpRunMode      run_mode,
                GimpImage       *image,
                gint             num_drawables,
                const GimpItem **drawables,
                GFile           *file)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RUN_MODE, run_mode,
                                          GIMP_TYPE_IMAGE, image,
                                          G_TYPE_INT, num_drawables,
                                          GIMP_TYPE_OBJECT_ARRAY, NULL,
                                          G_TYPE_FILE, file,
                                          G_TYPE_NONE);
  gimp_value_set_object_array (gimp_value_array_index (args, 3), GIMP_TYPE_ITEM, (GObject **) drawables, num_drawables);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-file-save",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_file_save_thumbnail:
 * @image: The image.
 * @file: The file the thumbnail belongs to.
 *
 * Saves a thumbnail for the given image
 *
 * This procedure saves a thumbnail for the given image according to
 * the Free Desktop Thumbnail Managing Standard. The thumbnail is saved
 * so that it belongs to the given file. This means you have to save
 * the image under this name first, otherwise this procedure will fail.
 * This procedure may become useful if you want to explicitly save a
 * thumbnail with a file.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_file_save_thumbnail (GimpImage *image,
                          GFile     *file)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_IMAGE, image,
                                          G_TYPE_FILE, file,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-file-save-thumbnail",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}
