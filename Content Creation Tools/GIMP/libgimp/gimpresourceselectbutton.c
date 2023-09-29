/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <gegl.h>
#include <gtk/gtk.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "gimp.h"

#include "gimpuitypes.h"
#include "gimpresourceselectbutton.h"
#include "gimpuimarshal.h"

#include "libgimp-intl.h"


/**
 * SECTION: gimpresourceselectbutton
 * @title: GimpResourceSelectButton
 * @short_description: Base class for buttons that popup a resource
 *                     selection dialog.
 *
 * A button which pops up a resource selection dialog.
 *
 * Subclasses: GimpFontSelectButton is a minimal one.
 * A subclass provides button trait (clickable),
 * but possibly not a GtkButton and may have many sub widgets.
 *
 * Responsibilities:
 *
 *     - implementing outer container widget,
 *     - managing clicks and popping up a remote chooser,
 *     - having a resource property,
 *     - signaling when user selects resource
 *     - receiving drag,
 *     - triggering draws of the button interior (by subclass) and draws of remote popup chooser.
 *
 * Collaborations:
 *
 *     - owned by GimpProcedureDialog via GimpPropWidget
 *     - resource property usually bound to a GimpConfig for a GimpPluginProcedure.
 *     - communicates using GimpResourceSelect with remote GimpPDBDialog,
 *       to choose an installed GimpResource owned by core.
 *
 * Subclass responsibilities:
 *
 *     - creating interior widgets
 *     - drawing the interior (a preview of the chosen resource)
 *     - declaring which interior widgets are drag destinations
 *     - declaring which interior widgets are clickable (generate "clicked" signal)
 *     - generate "clicked" (delegating to GtkButton or implementing from mouse events)
 *
 * Class is abstract and cannot be instantiated: no new () method.
 * Instead, instantiate a subclass.
 *
 * Since: 3.0
 **/


enum
{
  RESOURCE_SET,
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_TITLE,
  PROP_RESOURCE,
  N_PROPS
};


typedef struct
{
  GimpResource *resource;
  gchar        *title;
  const gchar  *temp_callback_from_remote_dialog;
  GtkWidget    *interior_widget;
} GimpResourceSelectButtonPrivate;


/*  local function prototypes  */

static void   gimp_resource_select_button_dispose      (GObject      *object);
static void   gimp_resource_select_button_finalize     (GObject      *object);

static void   gimp_resource_select_button_set_property (GObject      *object,
                                                        guint         property_id,
                                                        const GValue *value,
                                                        GParamSpec   *pspec);
static void   gimp_resource_select_button_get_property (GObject      *object,
                                                        guint         property_id,
                                                        GValue       *value,
                                                        GParamSpec   *pspec);

static void   gimp_resource_select_button_clicked  (GimpResourceSelectButton *self);

static void   gimp_resource_select_button_callback (GimpResource    *resource,
                                                    gboolean         dialog_closing,
                                                    gpointer         user_data);

static void   gimp_resource_select_drag_data_received (GimpResourceSelectButton *self,
                                                       GdkDragContext           *context,
                                                       gint                     x,
                                                       gint                     y,
                                                       GtkSelectionData        *selection,
                                                       guint                    info,
                                                       guint                    time);

static void   gimp_resource_select_button_set_remote_dialog (GimpResourceSelectButton *self,
                                                             GimpResource             *resource);

static void   gimp_resource_select_button_draw_interior     (GimpResourceSelectButton *self,
                                                             GimpResource             *resource);

static guint resource_button_signals[LAST_SIGNAL] = { 0 };
static GParamSpec *resource_button_props[N_PROPS] = { NULL, };

G_DEFINE_TYPE_WITH_PRIVATE (GimpResourceSelectButton, gimp_resource_select_button,
                            GTK_TYPE_BOX)


static void
gimp_resource_select_button_class_init (GimpResourceSelectButtonClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->dispose      = gimp_resource_select_button_dispose;
  object_class->finalize     = gimp_resource_select_button_finalize;
  object_class->set_property = gimp_resource_select_button_set_property;
  object_class->get_property = gimp_resource_select_button_get_property;

  klass->resource_set        = NULL;

  /**
   * GimpResourceSelectButton:title:
   *
   * The title to be used for the resource selection popup dialog.
   *
   * Since: 2.4
   */
  resource_button_props[PROP_TITLE] =
    g_param_spec_string ("title",
                         "Title",
                         "The title to be used for the resource selection popup dialog",
                         "Resource Selection",
                         GIMP_PARAM_READWRITE |
                         G_PARAM_CONSTRUCT_ONLY);

  /**
   * GimpResourceSelectButton:resource:
   *
   * The currently selected resource.
   *
   * Since: 2.4
   */
  resource_button_props[PROP_RESOURCE] =
    gimp_param_spec_resource ("resource",
                              "Resource",
                              "The currently selected resource",
                              TRUE,  /* none_ok */
                              GIMP_PARAM_READWRITE);

  g_object_class_install_properties (object_class,
                                     N_PROPS, resource_button_props);

  /**
   * GimpResourceSelectButton::resource-set:
   * @widget: the object which received the signal.
   * @resource: the currently selected resource.
   * @dialog_closing: whether the dialog was closed or not.
   *
   * The ::resource-set signal is emitted when the user selects a resource.
   *
   * Since: 2.4
   */
  resource_button_signals[RESOURCE_SET] =
    g_signal_new ("resource-set",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST,
                  G_STRUCT_OFFSET (GimpResourceSelectButtonClass, resource_set),
                  NULL, NULL,
                  _gimpui_marshal_VOID__POINTER_BOOLEAN,
                  G_TYPE_NONE, 2,
                  G_TYPE_OBJECT,
                  G_TYPE_BOOLEAN);
}

static void
gimp_resource_select_button_init (GimpResourceSelectButton *self)
{
  gtk_orientable_set_orientation (GTK_ORIENTABLE (self),
                                  GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_spacing (GTK_BOX (self), 6);
}

static void
gimp_resource_select_button_dispose (GObject *self)
{
  gimp_resource_select_button_close_popup (GIMP_RESOURCE_SELECT_BUTTON (self));

  G_OBJECT_CLASS (gimp_resource_select_button_parent_class)->dispose (self);
}

static void
gimp_resource_select_button_finalize (GObject *object)
{
  GimpResourceSelectButton *self = GIMP_RESOURCE_SELECT_BUTTON (object);
  GimpResourceSelectButtonPrivate *priv = gimp_resource_select_button_get_instance_private (self);

  g_clear_pointer (&priv->title, g_free);

  G_OBJECT_CLASS (gimp_resource_select_button_parent_class)->finalize (object);
}

/**
 * gimp_resource_select_button_set_drag_target:
 * @self: A #GimpResourceSelectButton
 * @drag_region_widget: An interior widget to be a droppable region
 *                      and emit "drag-data-received" signal
 * @drag_target: The drag target to accept
 *
 * Called by a subclass init to specialize the instance.
 *
 * Subclass knows its interior widget whose region is a drop zone.
 * Subclass knows what things can be dropped (target.)
 * Self (super) handles the drop.
 *
 * Since: 3.0
 **/
void
gimp_resource_select_button_set_drag_target (GimpResourceSelectButton *self,
                                             GtkWidget                *drag_region_widget,
                                             const GtkTargetEntry     *drag_target)
{
  g_return_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self));
  g_return_if_fail (drag_target != NULL);
  g_return_if_fail (drag_region_widget != NULL);

  gtk_drag_dest_set (drag_region_widget,
                     GTK_DEST_DEFAULT_HIGHLIGHT |
                     GTK_DEST_DEFAULT_MOTION |
                     GTK_DEST_DEFAULT_DROP,
                     drag_target, 1,  /* Pass array of size 1 */
                     GDK_ACTION_COPY);

  /* connect drag_region_widget's drag_received signal to self's callback. */
  g_signal_connect_swapped (drag_region_widget, "drag-data-received",
                            G_CALLBACK (gimp_resource_select_drag_data_received),
                            self);
}

/**
 * gimp_resource_select_button_set_clickable:
 * @self: A #GimpResourceSelectButton
 * @widget: An interior widget that emits "clicked" signal
 *
 * Called by a subclass init to specialize the instance.
 *
 * Subclass knows its interior widget whose region when clicked
 * should popup remote chooser.
 * Self handles the click event.
 *
 * Since: 3.0
 **/
void
gimp_resource_select_button_set_clickable (GimpResourceSelectButton *self,
                                           GtkWidget                *widget)
{
  g_return_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self));
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_WIDGET (widget));

  /* Require the widget have a signal "clicked", usually a button. */
  g_signal_connect_swapped (widget, "clicked",
                            G_CALLBACK (gimp_resource_select_button_clicked),
                            self);
}

/**
 * gimp_resource_select_button_get_resource:
 * @self: A #GimpResourceSelectButton
 *
 * Gets the currently selected resource.
 *
 * Returns: (transfer none): an internal copy of the resource which must not be freed.
 * You should ref and unref it when you want to own the resource.
 *
 * Since: 2.4
 */
GimpResource *
gimp_resource_select_button_get_resource (GimpResourceSelectButton *self)
{
  GimpResourceSelectButtonPrivate *priv;

  g_return_val_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self), NULL);

  priv = gimp_resource_select_button_get_instance_private (self);

  return priv->resource;
}

/**
 * gimp_resource_select_button_set_resource:
 * @self: A #GimpResourceSelectButton
 * @resource: Resource to set.
 *
 * Sets the currently selected resource.
 * This will select the resource in both the button and any chooser popup.
 *
 * Since: 2.4
 */
void
gimp_resource_select_button_set_resource (GimpResourceSelectButton *self,
                                          GimpResource             *resource)
{
  GimpResourceSelectButtonPrivate *priv;

  g_return_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self));
  g_return_if_fail (resource != NULL);

  priv = gimp_resource_select_button_get_instance_private (self);

  if (priv->temp_callback_from_remote_dialog)
    {
      /* A popup chooser dialog is already shown.
       * Call its setter to change the selection there
       * (since all views of the resource must be consistent.)
       * That will call back, which will change our own view of the resource.
       */
      gimp_resource_select_button_set_remote_dialog (self, resource);
    }
  else
    {
      /* Call our own setter. */
      gimp_resource_select_button_callback (resource, FALSE, self);
    }
}


/* Calls the virtual method of a similar name, which subclasses must override.
 *
 * resource: The instance to be drawn.
 *
 * A subclass knows how to draw its interior.
 * Called by super when the view is invalidated (needs to be redrawn.)
 * Not public.
 */
static void
gimp_resource_select_button_draw_interior (GimpResourceSelectButton  *self,
                                           GimpResource              *resource)
{
  GimpResourceSelectButtonClass *klass;

  g_return_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self));
  g_return_if_fail (GIMP_IS_RESOURCE (resource));

  klass = GIMP_RESOURCE_SELECT_BUTTON_GET_CLASS (self);

  g_return_if_fail (klass->draw_interior != NULL);

  klass->draw_interior (self);
}


/*  private functions  */

static void
gimp_resource_select_button_set_remote_dialog (GimpResourceSelectButton *self,
                                               GimpResource             *resource)
{
  GimpResourceSelectButtonPrivate *priv;
  GimpResourceSelectButtonClass   *klass;

  g_return_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self));
  g_return_if_fail (resource != NULL);

  priv = gimp_resource_select_button_get_instance_private (self);
  klass = GIMP_RESOURCE_SELECT_BUTTON_GET_CLASS (self);

  g_return_if_fail (klass->resource_type != G_TYPE_INVALID);

  /* The ultimate remote setter is e.g. gimp_fonts_set_popup, a PDB procedure.
   *
   * !!! Use the passed resource, not priv->resource.
   * Expect a callback which will change priv->resource.
   */
  gimp_resource_select_set (priv->temp_callback_from_remote_dialog,
                            resource,
                            klass->resource_type);
}

static void
gimp_resource_select_button_set_property (GObject      *object,
                                          guint         property_id,
                                          const GValue *gvalue,
                                          GParamSpec   *pspec)
{
  GimpResourceSelectButton        *self = GIMP_RESOURCE_SELECT_BUTTON (object);
  GimpResourceSelectButtonPrivate *priv = gimp_resource_select_button_get_instance_private (self);

  switch (property_id)
    {
    case PROP_TITLE:
      priv->title = g_value_dup_string (gvalue);
      break;

    case PROP_RESOURCE:
      priv->resource = g_value_get_object (gvalue);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_resource_select_button_get_property (GObject    *object,
                                          guint       property_id,
                                          GValue     *value,
                                          GParamSpec *pspec)
{
  GimpResourceSelectButton        *self = GIMP_RESOURCE_SELECT_BUTTON (object);
  GimpResourceSelectButtonPrivate *priv = gimp_resource_select_button_get_instance_private (self);

  switch (property_id)
    {
    case PROP_TITLE:
      g_value_set_string (value, priv->title);
      break;

    case PROP_RESOURCE:
      g_value_set_object (value, priv->resource);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

/* A callback from the remote resource select popup.
 * When user chooses a resource.
 * Via a temporary PDB procedure.
 *
 * Set self's model (priv->resource)
 * Notify any parent widget subscribed on the "resource" property
 * typically a prop widget.
 * Update the view, since model changed.
 */
static void
gimp_resource_select_button_callback (GimpResource *resource,
                                      gboolean      dialog_closing,
                                      gpointer      user_data)
{
  GimpResourceSelectButton        *self = GIMP_RESOURCE_SELECT_BUTTON (user_data);
  GimpResourceSelectButtonPrivate *priv = gimp_resource_select_button_get_instance_private (self);

  priv->resource = resource;

  /* Feedback user choice of resource into the look of the widget interior.
   * Call virtual method overridden by subclass.
   */
  gimp_resource_select_button_draw_interior (self, priv->resource);

  if (dialog_closing)
    priv->temp_callback_from_remote_dialog = NULL;

  g_signal_emit (self, resource_button_signals[RESOURCE_SET], 0,
                 resource, dialog_closing);
  g_object_notify_by_pspec (G_OBJECT (self),
                            resource_button_props[PROP_RESOURCE]);
}

static void
gimp_resource_select_button_clicked (GimpResourceSelectButton *self)
{
  GimpResourceSelectButtonPrivate *priv  = gimp_resource_select_button_get_instance_private (self);
  GimpResourceSelectButtonClass   *klass = GIMP_RESOURCE_SELECT_BUTTON_GET_CLASS (self);

  if (priv->temp_callback_from_remote_dialog)
    {
      /* Popup already created.  Calling setter raises the popup. */
      gimp_resource_select_button_set_remote_dialog (self, priv->resource);
    }
  else
    {
      /* Call GimpResourceSelect which dispatches on resource_type. */
      priv->temp_callback_from_remote_dialog =
        gimp_resource_select_new (priv->title,
                                  priv->resource,
                                  klass->resource_type,
                                  gimp_resource_select_button_callback,
                                  self,
                                  NULL);  /* No func to free data. */
    }
}


/* Drag methods. */

static void
gimp_resource_select_drag_data_received (GimpResourceSelectButton *self,
                                         GdkDragContext           *context,
                                         gint                      x,
                                         gint                      y,
                                         GtkSelectionData         *selection,
                                         guint                     info,
                                         guint                     time)
{
  gint   length = gtk_selection_data_get_length (selection);
  gchar *str;

  GimpResourceSelectButtonClass *klass;

  klass = GIMP_RESOURCE_SELECT_BUTTON_GET_CLASS (self);
  /* Require class resource_type was initialized. */
  g_assert (klass->resource_type != 0);

  /* Drag data is a string that is the ID of the resource. */

  if (gtk_selection_data_get_format (selection) != 8 || length < 1)
    {
      g_warning ("%s: received invalid resource data", G_STRFUNC);
      return;
    }

  str = g_strndup ((const gchar *) gtk_selection_data_get_data (selection),
                   length);

  if (g_utf8_validate (str, -1, NULL))
    {
      gint     pid;
      gpointer unused;
      gint     name_offset = 0;

      if (sscanf (str, "%i:%p:%n", &pid, &unused, &name_offset) >= 2 &&
          pid == gimp_getpid () && name_offset > 0)
        {
          gchar        *name = str + name_offset;
          GimpResource *resource;

          resource = gimp_resource_get_by_name (klass->resource_type, name);
          gimp_resource_select_button_set_resource (self, resource);
        }
    }

  g_free (str);
}


/**
 * gimp_resource_select_button_close_popup:
 * @self: A #GimpResourceSelectButton
 *
 * Closes the popup resource chooser dialog associated with @self.
 *
 * FUTURE: Possibly obsolete this by making it private,
 * since only called by script-fu-interface.c.
 * Might be needed if we allow plugins to implement their own dialogs.
 *
 * Since: 2.4
 */
void
gimp_resource_select_button_close_popup (GimpResourceSelectButton *self)
{
  GimpResourceSelectButtonPrivate *priv;

  g_return_if_fail (GIMP_IS_RESOURCE_SELECT_BUTTON (self));
  priv = gimp_resource_select_button_get_instance_private (self);

  if (priv->temp_callback_from_remote_dialog)
    {
      gimp_resource_select_destroy (priv->temp_callback_from_remote_dialog);

      priv->temp_callback_from_remote_dialog = NULL;
    }
  /* Else already closed. */
}
