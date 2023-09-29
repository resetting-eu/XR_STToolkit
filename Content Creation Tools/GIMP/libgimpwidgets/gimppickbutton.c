/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * gimppickbutton.c
 * Copyright (C) 2002 Michael Natterer <mitch@gimp.org>
 *
 * based on gtk+/gtk/gtkcolorsel.c
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
#include <gdk/gdkkeysyms.h>

#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif

#include "libgimpcolor/gimpcolor.h"

#include "gimpwidgetstypes.h"

#include "gimpcairo-utils.h"
#include "gimphelpui.h"
#include "gimpicons.h"
#include "gimppickbutton.h"
#include "gimppickbutton-private.h"

#include "libgimp/libgimp-intl.h"

#if defined (GDK_WINDOWING_QUARTZ)
#include "gimppickbutton-quartz.h"
#elif defined (GDK_WINDOWING_WIN32)
#include "gimppickbutton-win32.h"
#else
#include "gimppickbutton-default.h"
#include "gimppickbutton-kwin.h"
#include "gimppickbutton-xdg.h"
#endif

/**
 * SECTION: gimppickbutton
 * @title: GimpPickButton
 * @short_description: Widget to pick a color from screen.
 *
 * #GimpPickButton is a specialized button. When clicked, it changes
 * the cursor to a color-picker pipette and allows the user to pick a
 * color from any point on the screen.
 **/


enum
{
  COLOR_PICKED,
  LAST_SIGNAL
};


static void       gimp_pick_button_dispose         (GObject        *object);

static void       gimp_pick_button_clicked         (GtkButton      *button);


G_DEFINE_TYPE_WITH_PRIVATE (GimpPickButton, gimp_pick_button, GTK_TYPE_BUTTON)

#define parent_class gimp_pick_button_parent_class

static guint pick_button_signals[LAST_SIGNAL] = { 0 };


static void
gimp_pick_button_class_init (GimpPickButtonClass* klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkButtonClass *button_class = GTK_BUTTON_CLASS (klass);

  /**
   * GimpPickButton::color-picked:
   * @gimppickbutton: the object which received the signal.
   * @color: pointer to a #GimpRGB structure that holds the picked color
   *
   * This signal is emitted when the user has picked a color.
   **/
  pick_button_signals[COLOR_PICKED] =
    g_signal_new ("color-picked",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST,
                  G_STRUCT_OFFSET (GimpPickButtonClass, color_picked),
                  NULL, NULL, NULL,
                  G_TYPE_NONE, 1,
                  GIMP_TYPE_RGB);

  object_class->dispose = gimp_pick_button_dispose;

  button_class->clicked = gimp_pick_button_clicked;

  klass->color_picked   = NULL;
}

static void
gimp_pick_button_init (GimpPickButton *button)
{
  GtkWidget *image;

  button->priv = gimp_pick_button_get_instance_private (button);

  image = gtk_image_new_from_icon_name (GIMP_ICON_COLOR_PICK_FROM_SCREEN,
                                        GTK_ICON_SIZE_BUTTON);
  gtk_container_add (GTK_CONTAINER (button), image);
  gtk_widget_show (image);

  gimp_help_set_help_data (GTK_WIDGET (button),
                           _("Click the eyedropper, then click a color "
                             "anywhere on your screen to select that color."),
                           NULL);
}

static void
gimp_pick_button_dispose (GObject *object)
{
  GimpPickButton *button = GIMP_PICK_BUTTON (object);

  if (button->priv->cursor)
    {
      g_object_unref (button->priv->cursor);
      button->priv->cursor = NULL;
    }

  if (button->priv->grab_widget)
    {
      gtk_widget_destroy (button->priv->grab_widget);
      button->priv->grab_widget = NULL;
    }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

static void
gimp_pick_button_clicked (GtkButton *button)
{
#if defined (GDK_WINDOWING_QUARTZ)
  _gimp_pick_button_quartz_pick (GIMP_PICK_BUTTON (button));
#elif defined (GDK_WINDOWING_WIN32)
  _gimp_pick_button_win32_pick (GIMP_PICK_BUTTON (button));
#else
#ifdef GDK_WINDOWING_X11
  /* It's a bit weird as we use the default pick code both in first and
   * last cases. It's because when running GIMP on X11 in particular,
   * the portals don't return color space information. So the returned
   * color is in the display space, not in the current image space and
   * we have no way to convert the data back (well if running on X11, we
   * could still get a profile from the display, but if there are
   * several displays, we can't know for sure where the color was picked
   * from.).
   * See: https://github.com/flatpak/xdg-desktop-portal/issues/862
   */
  if (GDK_IS_X11_DISPLAY (gdk_display_get_default ()))
    _gimp_pick_button_default_pick (GIMP_PICK_BUTTON (button));
  else
#endif
  if (_gimp_pick_button_xdg_available ())
    _gimp_pick_button_xdg_pick (GIMP_PICK_BUTTON (button));
  else if (_gimp_pick_button_kwin_available ())
    _gimp_pick_button_kwin_pick (GIMP_PICK_BUTTON (button));
  else
    _gimp_pick_button_default_pick (GIMP_PICK_BUTTON (button));
#endif
}


/*  public functions  */

/**
 * gimp_pick_button_new:
 *
 * Creates a new #GimpPickButton widget.
 *
 * Returns: A new #GimpPickButton widget.
 **/
GtkWidget *
gimp_pick_button_new (void)
{
  return g_object_new (GIMP_TYPE_PICK_BUTTON, NULL);
}
