/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpresource_pdb.c
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
 * SECTION: gimpresource
 * @title: gimpresource
 * @short_description: Functions to manipulate resources.
 *
 * Functions to manipulate resources.
 **/


/**
 * _gimp_resource_get_by_name:
 * @type_name: The name of the resource type.
 * @resource_name: The name of the resource.
 *
 * Returns a resource with the given name.
 *
 * Returns a resource with the given name.
 *
 * Returns: (transfer none): The resource.
 *
 * Since: 3.0
 **/
GimpResource *
_gimp_resource_get_by_name (const gchar *type_name,
                            const gchar *resource_name)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpResource *resource = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_STRING, type_name,
                                          G_TYPE_STRING, resource_name,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-get-by-name",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    resource = GIMP_VALUES_GET_RESOURCE (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return resource;
}

/**
 * _gimp_resource_get_by_identifiers:
 * @type_name: The name of the resource type.
 * @resource_name: The name of the resource.
 * @collection: The collection identifier.
 * @is_internal: Whether this is the identifier for internal data.
 *
 * Returns the resource contained in a given file with a given name.
 *
 * Returns a resource specifically stored in a given file path, under a
 * given name (a single path may be a collection containing several
 * resources).
 *
 * Returns: (transfer none): The resource.
 *
 * Since: 3.0
 **/
GimpResource *
_gimp_resource_get_by_identifiers (const gchar *type_name,
                                   const gchar *resource_name,
                                   const gchar *collection,
                                   gboolean     is_internal)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpResource *resource = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_STRING, type_name,
                                          G_TYPE_STRING, resource_name,
                                          G_TYPE_STRING, collection,
                                          G_TYPE_BOOLEAN, is_internal,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-get-by-identifiers",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    resource = GIMP_VALUES_GET_RESOURCE (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return resource;
}

/**
 * gimp_resource_id_is_valid:
 * @resource_id: The resource ID to check.
 *
 * Returns TRUE if the resource ID is valid.
 *
 * This procedure checks if the given resource ID is valid and refers
 * to an existing resource.
 *
 * Returns: Whether the resource ID is valid.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_id_is_valid (gint resource_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean valid = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_INT, resource_id,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-id-is-valid",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    valid = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return valid;
}

/**
 * gimp_resource_id_is_brush:
 * @resource_id: The resource ID.
 *
 * Returns whether the resource ID is a brush.
 *
 * This procedure returns TRUE if the specified resource ID is a brush.
 *
 * Returns: TRUE if the resource ID is a brush, FALSE otherwise.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_id_is_brush (gint resource_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean brush = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_INT, resource_id,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-id-is-brush",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    brush = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return brush;
}

/**
 * gimp_resource_id_is_pattern:
 * @resource_id: The resource ID.
 *
 * Returns whether the resource ID is a pattern.
 *
 * This procedure returns TRUE if the specified resource ID is a
 * pattern.
 *
 * Returns: TRUE if the resource ID is a pattern, FALSE otherwise.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_id_is_pattern (gint resource_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean pattern = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_INT, resource_id,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-id-is-pattern",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    pattern = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return pattern;
}

/**
 * gimp_resource_id_is_gradient:
 * @resource_id: The resource ID.
 *
 * Returns whether the resource ID is a gradient.
 *
 * This procedure returns TRUE if the specified resource ID is a
 * gradient.
 *
 * Returns: TRUE if the resource ID is a gradient, FALSE otherwise.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_id_is_gradient (gint resource_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean gradient = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_INT, resource_id,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-id-is-gradient",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    gradient = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return gradient;
}

/**
 * gimp_resource_id_is_palette:
 * @resource_id: The resource ID.
 *
 * Returns whether the resource ID is a palette.
 *
 * This procedure returns TRUE if the specified resource ID is a
 * palette.
 *
 * Returns: TRUE if the resource ID is a palette, FALSE otherwise.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_id_is_palette (gint resource_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean palette = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_INT, resource_id,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-id-is-palette",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    palette = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return palette;
}

/**
 * gimp_resource_id_is_font:
 * @resource_id: The resource ID.
 *
 * Returns whether the resource ID is a font.
 *
 * This procedure returns TRUE if the specified resource ID is a font.
 *
 * Returns: TRUE if the resource ID is a font, FALSE otherwise.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_id_is_font (gint resource_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean font = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          G_TYPE_INT, resource_id,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-id-is-font",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    font = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return font;
}

/**
 * gimp_resource_get_name:
 * @resource: The resource.
 *
 * Returns the resource's name.
 *
 * This procedure returns the resource's name.
 *
 * Returns: (transfer full): The resource's name.
 *          The returned value must be freed with g_free().
 *
 * Since: 3.0
 **/
gchar *
gimp_resource_get_name (GimpResource *resource)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gchar *name = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RESOURCE, resource,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-get-name",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    name = GIMP_VALUES_DUP_STRING (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return name;
}

/**
 * _gimp_resource_get_identifiers:
 * @resource: The resource.
 * @name: (out) (transfer full): The resource's name.
 * @collection_id: (out) (transfer full): The resource's collection identifier.
 *
 * Returns a triplet identifying the resource.
 *
 * This procedure returns 2 strings and a boolean. The first string is
 * the resource name, similar to what you would obtain calling
 * gimp_resource_get_name(). The second is an opaque identifier for the
 * collection this resource belongs to.
 * Note: as far as GIMP is concerned, a collection of resource usually
 * corresponds to a single file on disk (which may or may not contain
 * several resources). Therefore the identifier may be derived from the
 * local file path. Nevertheless you should not use this string as such
 * as this is not guaranteed to be always the case. You should consider
 * it as an opaque identifier only to be used again through
 * _gimp_resource_get_by_identifier().
 *
 * Returns: Whether this is the identifier for internal data.
 *
 * Since: 3.0
 **/
gboolean
_gimp_resource_get_identifiers (GimpResource  *resource,
                                gchar        **name,
                                gchar        **collection_id)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean is_internal = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RESOURCE, resource,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-get-identifiers",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    {
      is_internal = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);
      *name = GIMP_VALUES_DUP_STRING (return_vals, 2);
      *collection_id = GIMP_VALUES_DUP_STRING (return_vals, 3);
    }

  gimp_value_array_unref (return_vals);

  return is_internal;
}

/**
 * gimp_resource_is_editable:
 * @resource: The resource.
 *
 * Whether the resource can be edited.
 *
 * Returns TRUE if you have permission to change the resource.
 *
 * Returns: TRUE if the resource can be edited.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_is_editable (GimpResource *resource)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean editable = FALSE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RESOURCE, resource,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-is-editable",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    editable = GIMP_VALUES_GET_BOOLEAN (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return editable;
}

/**
 * gimp_resource_duplicate:
 * @resource: The resource.
 *
 * Duplicates a resource.
 *
 * Returns a copy having a different, unique ID.
 *
 * Returns: (transfer none): A copy of the resource.
 *
 * Since: 3.0
 **/
GimpResource *
gimp_resource_duplicate (GimpResource *resource)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  GimpResource *resource_copy = NULL;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RESOURCE, resource,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-duplicate",
                                              args);
  gimp_value_array_unref (args);

  if (GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS)
    resource_copy = GIMP_VALUES_GET_RESOURCE (return_vals, 1);

  gimp_value_array_unref (return_vals);

  return resource_copy;
}

/**
 * gimp_resource_rename:
 * @resource: The resource.
 * @new_name: The proposed new name of the resource.
 *
 * Renames a resource. When the name is in use, renames to a unique
 * name.
 *
 * Renames a resource. When the proposed name is already used, GIMP
 * generates a unique name.
 *
 * Returns: TRUE on success.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_rename (GimpResource *resource,
                      const gchar  *new_name)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RESOURCE, resource,
                                          G_TYPE_STRING, new_name,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-rename",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}

/**
 * gimp_resource_delete:
 * @resource: The resource.
 *
 * Deletes a resource.
 *
 * Deletes a resource. Returns an error if the resource is not
 * deletable. Deletes the resource's data. You should not use the
 * resource afterwards.
 *
 * Returns: TRUE on success.
 *
 * Since: 3.0
 **/
gboolean
gimp_resource_delete (GimpResource *resource)
{
  GimpValueArray *args;
  GimpValueArray *return_vals;
  gboolean success = TRUE;

  args = gimp_value_array_new_from_types (NULL,
                                          GIMP_TYPE_RESOURCE, resource,
                                          G_TYPE_NONE);

  return_vals = gimp_pdb_run_procedure_array (gimp_get_pdb (),
                                              "gimp-resource-delete",
                                              args);
  gimp_value_array_unref (args);

  success = GIMP_VALUES_GET_ENUM (return_vals, 0) == GIMP_PDB_SUCCESS;

  gimp_value_array_unref (return_vals);

  return success;
}
