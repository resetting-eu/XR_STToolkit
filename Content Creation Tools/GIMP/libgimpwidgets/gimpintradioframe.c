/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * gimpintradioframe.c
 * Copyright (C) 2022 Jehan
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

#include "config.h"

#include <libintl.h>

#include <gtk/gtk.h>

#include "libgimpbase/gimpbase.h"

#include "gimpwidgetstypes.h"

#include "gimpintradioframe.h"
#include "gimpintstore.h"


/**
 * SECTION: gimpintradioframe
 * @title: GimpIntRadioFrame
 * @short_description: A widget providing radio buttons for integer
 *                     values (e.g. enums).
 *
 * A widget providing a frame with title, containing grouped radio
 * buttons, each associated with an integer value and random user data.
 **/


enum
{
  PROP_0,
  PROP_VALUE,
  PROP_STORE,
};


typedef struct _GimpIntRadioFramePrivate GimpIntRadioFramePrivate;

struct _GimpIntRadioFramePrivate
{
  gchar                            *label;
  GimpIntStore                     *store;
  GSList                           *group;
  gint                              value;

  GtkWidget                        *box;

  GimpIntRadioFrameSensitivityFunc  sensitivity_func;
  gpointer                          sensitivity_data;
  GDestroyNotify                    sensitivity_destroy;
};

#define GET_PRIVATE(obj) ((GimpIntRadioFramePrivate *) gimp_int_radio_frame_get_instance_private ((GimpIntRadioFrame *) obj))


static void  gimp_int_radio_frame_constructed        (GObject           *object);
static void  gimp_int_radio_frame_finalize           (GObject           *object);
static void  gimp_int_radio_frame_set_property       (GObject           *object,
                                                      guint              property_id,
                                                      const GValue      *value,
                                                      GParamSpec        *pspec);
static void  gimp_int_radio_frame_get_property       (GObject           *object,
                                                      guint              property_id,
                                                      GValue            *value,
                                                      GParamSpec        *pspec);

static gboolean gimp_int_radio_frame_draw            (GtkWidget         *widget,
                                                      cairo_t           *cr,
                                                      gpointer           user_data);

static void  gimp_int_radio_frame_fill               (GimpIntRadioFrame *frame);
static void  gimp_int_radio_frame_set_store          (GimpIntRadioFrame *frame,
                                                      GimpIntStore      *store);
static void  gimp_int_radio_frame_update_sensitivity (GimpIntRadioFrame *frame);

static void  gimp_int_radio_frame_button_toggled     (GtkToggleButton   *button,
                                                     GimpIntRadioFrame *frame);


G_DEFINE_TYPE_WITH_PRIVATE (GimpIntRadioFrame, gimp_int_radio_frame,
                            GIMP_TYPE_FRAME)

#define parent_class gimp_int_radio_frame_parent_class


static void
gimp_int_radio_frame_class_init (GimpIntRadioFrameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->constructed  = gimp_int_radio_frame_constructed;
  object_class->finalize     = gimp_int_radio_frame_finalize;
  object_class->set_property = gimp_int_radio_frame_set_property;
  object_class->get_property = gimp_int_radio_frame_get_property;

  /**
   * GimpIntRadioFrame:value:
   *
   * The active value
   *
   * Since: 3.0
   */
  g_object_class_install_property (object_class, PROP_VALUE,
                                   g_param_spec_int ("value",
                                                     "Value",
                                                     "Value of active item",
                                                     G_MININT, G_MAXINT, 0,
                                                     GIMP_PARAM_READWRITE |
                                                     G_PARAM_EXPLICIT_NOTIFY));

  /**
   * GimpIntRadioFrame:store:
   *
   * The %GimpIntStore from which the radio frame takes the values shown
   * in the list.
   *
   * Since: 3.0
   */
  g_object_class_install_property (object_class,
                                   PROP_STORE,
                                   g_param_spec_object ("store",
                                                        "GimpRadioFrame int store",
                                                        "The int store for the radio frame",
                                                        GIMP_TYPE_INT_STORE,
                                                        GIMP_PARAM_READWRITE |
                                                        G_PARAM_EXPLICIT_NOTIFY));
}

static void
gimp_int_radio_frame_init (GimpIntRadioFrame *radio_frame)
{
  GimpIntRadioFramePrivate *priv = GET_PRIVATE (radio_frame);

  priv->box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gtk_container_add (GTK_CONTAINER (radio_frame), priv->box);
  gtk_widget_show (GTK_WIDGET (priv->box));
}

static void
gimp_int_radio_frame_constructed (GObject *object)
{
  G_OBJECT_CLASS (parent_class)->constructed (object);

  g_signal_connect (object, "draw",
                    G_CALLBACK (gimp_int_radio_frame_draw),
                    NULL);
}

static void
gimp_int_radio_frame_finalize (GObject *object)
{
  GimpIntRadioFramePrivate *priv = GET_PRIVATE (object);

  g_clear_pointer (&priv->label, g_free);
  g_clear_object (&priv->store);
  g_clear_pointer (&priv->group, g_slist_free);

  if (priv->sensitivity_destroy)
    {
      GDestroyNotify d = priv->sensitivity_destroy;

      priv->sensitivity_destroy = NULL;
      d (priv->sensitivity_data);
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gimp_int_radio_frame_set_property (GObject      *object,
                                   guint         property_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  switch (property_id)
    {
    case PROP_VALUE:
      gimp_int_radio_frame_set_active (GIMP_INT_RADIO_FRAME (object),
                                       g_value_get_int (value));
      break;
    case PROP_STORE:
      gimp_int_radio_frame_set_store (GIMP_INT_RADIO_FRAME (object),
                                      g_value_get_object (value));
      break;


    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_int_radio_frame_get_property (GObject    *object,
                                   guint       property_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  GimpIntRadioFramePrivate *priv = GET_PRIVATE (object);

  switch (property_id)
    {
    case PROP_VALUE:
      g_value_set_int (value, priv->value);
    break;
      case PROP_STORE:
        g_value_set_object (value, priv->store);
        break;


    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

/* Public functions */

/**
 * gimp_int_radio_frame_new_from_store:
 * @title: the frame label.
 * @store: the %GimpIntStore to generate radio buttons from.
 *
 * Creates a %GimpIntRadioFrame containing radio buttons for each item
 * in the @store. The created widget takes ownership of @store.
 *
 * If you need to construct an empty #GimpIntRadioFrame, it's best to use
 * g_object_new (GIMP_TYPE_INT_RADIO_FRAME, NULL).
 *
 * Returns: a new #GimpIntRadioFrame.
 *
 * Since: 3.0
 **/
GtkWidget *
gimp_int_radio_frame_new_from_store (const gchar  *title,
                                     GimpIntStore *store)
{
  GtkWidget *radio_frame;

  radio_frame = g_object_new (GIMP_TYPE_INT_RADIO_FRAME,
                              "label", title,
                              "store", store,
                              NULL);

  return radio_frame;
}

/**
 * gimp_int_radio_frame_new: (skip)
 * @first_label: the label of the first item
 * @first_value: the value of the first item
 * @...: a %NULL terminated list of more label, value pairs
 *
 * Creates a GtkComboBox that has integer values associated with each
 * item. The items to fill the combo box with are specified as a %NULL
 * terminated list of label/value pairs.
 *
 * If you need to construct an empty #GimpIntRadioFrame, it's best to use
 * g_object_new (GIMP_TYPE_INT_RADIO_FRAME, NULL).
 *
 * Returns: a new #GimpIntRadioFrame.
 *
 * Since: 3.0
 **/
GtkWidget *
gimp_int_radio_frame_new (const gchar *first_label,
                          gint         first_value,
                          ...)
{
  GtkWidget *radio_frame;
  va_list    args;

  va_start (args, first_value);

  radio_frame = gimp_int_radio_frame_new_valist (first_label, first_value, args);

  va_end (args);

  return radio_frame;
}

/**
 * gimp_int_radio_frame_new_valist: (skip)
 * @first_label: the label of the first item
 * @first_value: the value of the first item
 * @values: a va_list with more values
 *
 * A variant of gimp_int_radio_frame_new() that takes a va_list of
 * label/value pairs.
 *
 * Returns: a new #GimpIntRadioFrame.
 *
 * Since: 3.0
 **/
GtkWidget *
gimp_int_radio_frame_new_valist (const gchar *first_label,
                                 gint         first_value,
                                 va_list      values)
{
  GtkWidget    *radio_frame;
  GtkListStore *store;

  store = gimp_int_store_new_valist (first_label, first_value, values);

  radio_frame = g_object_new (GIMP_TYPE_INT_RADIO_FRAME,
                              "store", store,
                              NULL);

  return radio_frame;
}

/**
 * gimp_int_radio_frame_new_array: (rename-to gimp_int_radio_frame_new)
 * @labels: (array zero-terminated=1): a %NULL-terminated array of labels.
 *
 * A variant of gimp_int_radio_frame_new() that takes an array of labels.
 * The array indices are used as values.
 *
 * Returns: a new #GimpIntRadioFrame.
 *
 * Since: 3.0
 **/
GtkWidget *
gimp_int_radio_frame_new_array (const gchar *labels[])
{
  GtkWidget                *frame;
  GimpIntRadioFramePrivate *priv;
  GtkListStore             *store;
  gint                      i;

  g_return_val_if_fail (labels != NULL, NULL);

  frame = g_object_new (GIMP_TYPE_INT_RADIO_FRAME, NULL);
  priv  = GET_PRIVATE (frame);
  store = GTK_LIST_STORE (priv->store);

  for (i = 0; labels[i] != NULL; i++)
    {
      GtkTreeIter  iter;

      if (labels[i])
        {
          gtk_list_store_append (store, &iter);
          gtk_list_store_set (store, &iter,
                              GIMP_INT_STORE_VALUE, i,
                              GIMP_INT_STORE_LABEL, labels[i],
                              -1);
        }
    }

  return frame;
}

/**
 * gimp_int_radio_frame_prepend: (skip)
 * @radio_frame: a #GimpIntRadioFrame
 * @...:       pairs of column number and value, terminated with -1
 *
 * This function provides a convenient way to prepend items to a
 * #GimpIntRadioFrame. It prepends a row to the @radio_frame's list store
 * and calls gtk_list_store_set() for you.
 *
 * The column number must be taken from the enum #GimpIntStoreColumns.
 *
 * Since: 3.0
 **/
void
gimp_int_radio_frame_prepend (GimpIntRadioFrame *radio_frame,
                            ...)
{
  GtkListStore             *store;
  GimpIntRadioFramePrivate *priv;
  GtkTreeIter               iter;
  va_list                   args;

  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (radio_frame));

  priv  = GET_PRIVATE (radio_frame);
  store = GTK_LIST_STORE (priv->store);

  va_start (args, radio_frame);

  gtk_list_store_prepend (store, &iter);
  gtk_list_store_set_valist (store, &iter, args);

  va_end (args);
}

/**
 * gimp_int_radio_frame_append: (skip)
 * @radio_frame: a #GimpIntRadioFrame
 * @...:         pairs of column number and value, terminated with -1
 *
 * This function provides a convenient way to append items to a
 * #GimpIntRadioFrame. It appends a row to the @radio_frame's list store
 * and calls gtk_list_store_set() for you.
 *
 * The column number must be taken from the enum #GimpIntStoreColumns.
 *
 * Since: 3.0
 **/
void
gimp_int_radio_frame_append (GimpIntRadioFrame *radio_frame,
                             ...)
{
  GtkListStore             *store;
  GimpIntRadioFramePrivate *priv;
  GtkTreeIter               iter;
  va_list                   args;

  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (radio_frame));

  priv  = GET_PRIVATE (radio_frame);
  store = GTK_LIST_STORE (priv->store);

  va_start (args, radio_frame);

  gtk_list_store_append (store, &iter);
  gtk_list_store_set_valist (store, &iter, args);

  va_end (args);
}

/**
 * gimp_int_radio_frame_set_active:
 * @radio_frame: a #GimpIntRadioFrame
 * @value:       an integer value
 *
 * Looks up the item that belongs to the given @value and makes it the
 * selected item in the @radio_frame.
 *
 * Returns: %TRUE on success (value changed or not) or %FALSE if there
 *          was no item for this value.
 *
 * Since: 3.0
 **/
gboolean
gimp_int_radio_frame_set_active (GimpIntRadioFrame *frame,
                                 gint               value)
{
  GimpIntRadioFramePrivate *priv = GET_PRIVATE (frame);
  GtkWidget                *button;
  GSList                   *iter = priv->group;

  g_return_val_if_fail (GIMP_IS_INT_RADIO_FRAME (frame), FALSE);

  for (; iter; iter = g_slist_next (iter))
    {
      button = GTK_WIDGET (iter->data);

      if (g_object_get_data (G_OBJECT (button), "gimp-radio-frame-value") ==
          GINT_TO_POINTER (value))
        {
          if (! gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)))
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);

          return TRUE;
        }
    }

  return FALSE;
}

/**
 * gimp_int_radio_frame_get_active:
 * @radio_frame: a #GimpIntRadioFrame
 *
 * Returns: the value of the active item.
 *
 * Since:3.0
 **/
gint
gimp_int_radio_frame_get_active (GimpIntRadioFrame *frame)
{
  GimpIntRadioFramePrivate *priv = GET_PRIVATE (frame);

  g_return_val_if_fail (GIMP_IS_INT_RADIO_FRAME (frame), FALSE);

  return priv->value;
}

/**
 * gimp_int_radio_frame_set_active_by_user_data:
 * @radio_frame: a #GimpIntRadioFrame
 * @user_data: an integer value
 *
 * Looks up the item that has the given @user_data and makes it the
 * selected item in the @radio_frame.
 *
 * Returns: %TRUE on success or %FALSE if there was no item for
 *          this user-data.
 *
 * Since: 3.0
 **/
gboolean
gimp_int_radio_frame_set_active_by_user_data (GimpIntRadioFrame *radio_frame,
                                              gpointer           user_data)
{
  GimpIntRadioFramePrivate *priv;
  GtkTreeIter               iter;

  g_return_val_if_fail (GIMP_IS_INT_RADIO_FRAME (radio_frame), FALSE);

  priv = GET_PRIVATE (radio_frame);

  if (gimp_int_store_lookup_by_user_data (GTK_TREE_MODEL (priv->store), user_data, &iter))
    {
      gint value;

      gtk_tree_model_get (GTK_TREE_MODEL (priv->store), &iter,
                          GIMP_INT_STORE_VALUE, &value,
                          -1);
      gimp_int_radio_frame_set_active (radio_frame, value);

      return TRUE;
    }

  return FALSE;
}

/**
 * gimp_int_radio_frame_get_active_user_data:
 * @radio_frame: a #GimpIntRadioFrame
 * @user_data: (out) (transfer none): return location for the gpointer value
 *
 * Retrieves the user-data of the selected (active) item in the @radio_frame.
 *
 * Returns: %TRUE if @user_data has been set or %FALSE if no item was
 *               active.
 *
 * Since: 3.0
 **/
gboolean
gimp_int_radio_frame_get_active_user_data (GimpIntRadioFrame *radio_frame,
                                           gpointer          *user_data)
{
  GimpIntRadioFramePrivate *priv;
  GtkTreeIter               iter;

  g_return_val_if_fail (GIMP_IS_INT_RADIO_FRAME (radio_frame), FALSE);
  g_return_val_if_fail (user_data != NULL, FALSE);

  priv = GET_PRIVATE (radio_frame);

  if (gimp_int_store_lookup_by_value (GTK_TREE_MODEL (priv->store), priv->value, &iter))
    {
      gtk_tree_model_get (GTK_TREE_MODEL (priv->store), &iter,
                          GIMP_INT_STORE_USER_DATA,      user_data,
                          -1);
      return TRUE;
    }

  return FALSE;
}

/**
 * gimp_int_radio_frame_set_sensitivity:
 * @radio_frame: a #GimpIntRadioFrame
 * @func: a function that returns a boolean value, or %NULL to unset
 * @data: data to pass to @func
 * @destroy: destroy notification for @data
 *
 * Sets a function that is used to decide about the sensitivity of radio
 * buttons in the @radio_frame. Use this if you want to set certain
 * radio buttons insensitive.
 *
 * Calling gtk_widget_queue_draw() on the @radio_frame will cause the
 * sensitivity to be updated.
 *
 * Since: 3.0
 **/
void
gimp_int_radio_frame_set_sensitivity (GimpIntRadioFrame      *radio_frame,
                                      GimpIntRadioFrameSensitivityFunc  func,
                                      gpointer                data,
                                      GDestroyNotify          destroy)
{
  GimpIntRadioFramePrivate *priv;

  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (radio_frame));

  priv = GET_PRIVATE (radio_frame);

  if (priv->sensitivity_destroy)
    {
      GDestroyNotify destroy = priv->sensitivity_destroy;

      priv->sensitivity_destroy = NULL;
      destroy (priv->sensitivity_data);
    }

  priv->sensitivity_func    = func;
  priv->sensitivity_data    = data;
  priv->sensitivity_destroy = destroy;
}


/* Private functions */

static gboolean
gimp_int_radio_frame_draw (GtkWidget *widget,
                           cairo_t   *cr,
                           gpointer   user_data)
{
  gimp_int_radio_frame_update_sensitivity (GIMP_INT_RADIO_FRAME (widget));

  return FALSE;
}

static void
gimp_int_radio_frame_fill (GimpIntRadioFrame *frame)
{
  GimpIntRadioFramePrivate *priv;

  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (frame));

  priv = GET_PRIVATE (frame);

  g_clear_pointer (&priv->group, g_slist_free);
  gtk_container_foreach (GTK_CONTAINER (priv->box),
                         (GtkCallback) gtk_widget_destroy, NULL);

  if (priv->store)
    {
      GtkTreeModel *model;
      GSList       *group = NULL;
      GtkTreeIter   iter;
      gboolean      iter_valid;

      model = GTK_TREE_MODEL (priv->store);

      for (iter_valid = gtk_tree_model_get_iter_first (model, &iter);
           iter_valid;
           iter_valid = gtk_tree_model_iter_next (model, &iter))
        {
          GtkWidget *button;
          gchar     *label;
          gint       value;

          gtk_tree_model_get (model, &iter,
                              GIMP_INT_STORE_LABEL, &label,
                              GIMP_INT_STORE_VALUE, &value,
                              -1);

          button = gtk_radio_button_new_with_mnemonic (group, label);
          gtk_box_pack_start (GTK_BOX (priv->box), button, FALSE, FALSE, 0);
          gtk_widget_show (button);

          g_free (label);

          group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (button));

          g_object_set_data (G_OBJECT (button), "gimp-radio-frame-value",
                             GINT_TO_POINTER (value));

          g_signal_connect (button, "toggled",
                            G_CALLBACK (gimp_int_radio_frame_button_toggled),
                            frame);
        }
      priv->group = g_slist_copy (group);

      gimp_int_radio_frame_set_active (frame, priv->value);
    }
}

static void
gimp_int_radio_frame_set_store (GimpIntRadioFrame *frame,
                                GimpIntStore      *store)
{
  GimpIntRadioFramePrivate *priv;

  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (frame));
  g_return_if_fail (GIMP_IS_INT_STORE (store));

  priv = GET_PRIVATE (frame);

  if (priv->store == store)
    return;

  if (priv->store)
    {
      g_signal_handlers_disconnect_by_func (priv->store,
                                            (GCallback) gimp_int_radio_frame_fill,
                                            NULL);
      g_object_unref (priv->store);
    }

  priv->store = g_object_ref (store);

  if (priv->store)
    {
      g_signal_connect_object (priv->store, "row-changed",
                               (GCallback) gimp_int_radio_frame_fill,
                               frame, G_CONNECT_SWAPPED);
      g_signal_connect_object (priv->store, "row-deleted",
                               (GCallback) gimp_int_radio_frame_fill,
                               frame, G_CONNECT_SWAPPED);
      g_signal_connect_object (priv->store, "row-inserted",
                               (GCallback) gimp_int_radio_frame_fill,
                               frame, G_CONNECT_SWAPPED);
      g_signal_connect_object (priv->store, "rows-reordered",
                               (GCallback) gimp_int_radio_frame_fill,
                               frame, G_CONNECT_SWAPPED);
    }

  gimp_int_radio_frame_fill (frame);

  g_object_notify (G_OBJECT (frame), "store");
}

static void
gimp_int_radio_frame_update_sensitivity (GimpIntRadioFrame *frame)
{
  GimpIntRadioFramePrivate *priv = GET_PRIVATE (frame);
  GSList                   *iter = priv->group;

  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (frame));

  if (! priv->sensitivity_func)
    return;

  for (; iter; iter = g_slist_next (iter))
    {
      GtkWidget   *button = GTK_WIDGET (iter->data);
      GtkTreeIter  tree_iter;
      gint         value;

      value = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (button), "gimp-radio-frame-value"));

      gtk_widget_set_sensitive (button, TRUE);
      if (gimp_int_store_lookup_by_value (GTK_TREE_MODEL (priv->store), value, &tree_iter))
        {
          gpointer user_data;
          gint     new_value = value;

          gtk_tree_model_get (GTK_TREE_MODEL (priv->store), &tree_iter,
                              GIMP_INT_STORE_USER_DATA,     &user_data,
                              -1);
          if (! priv->sensitivity_func (value, user_data, &new_value,
                                        priv->sensitivity_data))
            {
              if (new_value != value)
                gimp_int_radio_frame_set_active (frame, new_value);

              gtk_widget_set_sensitive (button, FALSE);
            }
        }
    }
}

static void
gimp_int_radio_frame_button_toggled (GtkToggleButton   *button,
                                     GimpIntRadioFrame *frame)
{
  g_return_if_fail (GIMP_IS_INT_RADIO_FRAME (frame));
  g_return_if_fail (GTK_IS_RADIO_BUTTON (button));

  if (gtk_toggle_button_get_active (button))
    {
      GimpIntRadioFramePrivate *priv = GET_PRIVATE (frame);
      gint                      value;

      value = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (button), "gimp-radio-frame-value"));

      if (priv->value != value)
        {
          priv->value = value;
          g_object_notify (G_OBJECT (frame), "value");
        }
    }
}
