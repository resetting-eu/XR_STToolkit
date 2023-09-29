/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * gimpprogressbar.c
 * Copyright (C) 2004 Michael Natterer <mitch@gimp.org>
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

#include <gtk/gtk.h>

#ifdef GDK_WINDOWING_WIN32
#include <gdk/gdkwin32.h>
#endif

#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif

#ifdef GDK_WINDOWING_WAYLAND
#include <gdk/gdkwayland.h>
#endif

#include "gimpuitypes.h"

#include "gimp.h"

#include "gimpprogressbar.h"


/**
 * SECTION: gimpprogressbar
 * @title: GimpProgressBar
 * @short_description: A widget providing a progress bar.
 *
 * A widget providing a progress bar that automatically redirects any
 * progress calls to itself.
 **/


static void     gimp_progress_bar_dispose    (GObject     *object);

static void     gimp_progress_bar_start      (const gchar *message,
                                              gboolean     cancelable,
                                              gpointer     user_data);
static void     gimp_progress_bar_end        (gpointer     user_data);
static void     gimp_progress_bar_set_text   (const gchar *message,
                                              gpointer     user_data);
static void     gimp_progress_bar_set_value  (gdouble      percentage,
                                              gpointer     user_data);
static void     gimp_progress_bar_pulse      (gpointer     user_data);
static guint64  gimp_progress_bar_get_window (gpointer     user_data);


G_DEFINE_TYPE (GimpProgressBar, gimp_progress_bar, GTK_TYPE_PROGRESS_BAR)

#define parent_class gimp_progress_bar_parent_class


static void
gimp_progress_bar_class_init (GimpProgressBarClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->dispose = gimp_progress_bar_dispose;
}

static void
gimp_progress_bar_init (GimpProgressBar *bar)
{
  GimpProgressVtable vtable = { 0, };

  gtk_progress_bar_set_text (GTK_PROGRESS_BAR (bar), " ");
  gtk_progress_bar_set_ellipsize (GTK_PROGRESS_BAR (bar), PANGO_ELLIPSIZE_END);

  vtable.start      = gimp_progress_bar_start;
  vtable.end        = gimp_progress_bar_end;
  vtable.set_text   = gimp_progress_bar_set_text;
  vtable.set_value  = gimp_progress_bar_set_value;
  vtable.pulse      = gimp_progress_bar_pulse;
  vtable.get_window = gimp_progress_bar_get_window;

  bar->progress_callback = gimp_progress_install_vtable (&vtable, bar, NULL);
}

static void
gimp_progress_bar_dispose (GObject *object)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (object);

  if (bar->progress_callback)
    {
      gimp_progress_uninstall (bar->progress_callback);
      bar->progress_callback = NULL;
    }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

static void
gimp_progress_bar_start (const gchar *message,
                         gboolean     cancelable,
                         gpointer     user_data)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (user_data);

  gtk_progress_bar_set_text (GTK_PROGRESS_BAR (bar), message ? message : " ");
  gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (bar), 0.0);

  if (gtk_widget_is_drawable (GTK_WIDGET (bar)))
    while (gtk_events_pending ())
      gtk_main_iteration ();
}

static void
gimp_progress_bar_end (gpointer user_data)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (user_data);

  gtk_progress_bar_set_text (GTK_PROGRESS_BAR (bar), " ");
  gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (bar), 0.0);

  if (gtk_widget_is_drawable (GTK_WIDGET (bar)))
    while (gtk_events_pending ())
      gtk_main_iteration ();
}

static void
gimp_progress_bar_set_text (const gchar *message,
                            gpointer     user_data)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (user_data);

  gtk_progress_bar_set_text (GTK_PROGRESS_BAR (bar), message ? message : " ");

  if (gtk_widget_is_drawable (GTK_WIDGET (bar)))
    while (gtk_events_pending ())
      gtk_main_iteration ();
}

static void
gimp_progress_bar_set_value (gdouble  percentage,
                             gpointer user_data)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (user_data);

  if (percentage >= 0.0)
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (bar), percentage);
  else
    gtk_progress_bar_pulse (GTK_PROGRESS_BAR (bar));

  if (gtk_widget_is_drawable (GTK_WIDGET (bar)))
    while (gtk_events_pending ())
      gtk_main_iteration ();
}

static void
gimp_progress_bar_pulse (gpointer user_data)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (user_data);

  gtk_progress_bar_pulse (GTK_PROGRESS_BAR (bar));

  if (gtk_widget_is_drawable (GTK_WIDGET (bar)))
    while (gtk_events_pending ())
      gtk_main_iteration ();
}

static guint64
gimp_window_get_native_id (GtkWindow *window)
{
  GdkWindow *surface;

  g_return_val_if_fail (GTK_IS_WINDOW (window), 0);

  surface = gtk_widget_get_window (GTK_WIDGET (window));
  if (!surface) /* aka window is not yet realized */
    return 0;

#ifdef GDK_WINDOWING_WIN32
  if (GDK_IS_WIN32_WINDOW (surface))
    return GPOINTER_TO_INT (GDK_WINDOW_HWND (gtk_widget_get_window (GTK_WIDGET (window))));
#endif

#ifdef GDK_WINDOWING_X11
  if (GDK_IS_X11_WINDOW (surface))
    return GPOINTER_TO_INT (GDK_WINDOW_XID (gtk_widget_get_window (GTK_WIDGET (window))));
#endif

#ifdef GDK_WINDOWING_WAYLAND
  if (GDK_IS_WAYLAND_WINDOW (surface))
    g_debug ("Getting window ID for progress not supported on Wayland yet");
#endif

  return 0;
}

static guint64
gimp_progress_bar_get_window (gpointer user_data)
{
  GimpProgressBar *bar = GIMP_PROGRESS_BAR (user_data);
  GtkWidget       *toplevel;

  toplevel = gtk_widget_get_toplevel (GTK_WIDGET (bar));

  if (GTK_IS_WINDOW (toplevel))
    return gimp_window_get_native_id (GTK_WINDOW (toplevel));

  return 0;
}

/**
 * gimp_progress_bar_new:
 *
 * Creates a new #GimpProgressBar widget.
 *
 * Returns: the new widget.
 *
 * Since: 2.2
 **/
GtkWidget *
gimp_progress_bar_new (void)
{
  return g_object_new (GIMP_TYPE_PROGRESS_BAR, NULL);
}
