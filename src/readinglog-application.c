/* MIT License
 *
 * Copyright (c) 2025 Broc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <glib/gi18n.h>

#include "readinglog-application.h"
#include "readinglog-window.h"

struct _ReadinglogApplication
{
	GtkApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (ReadinglogApplication, readinglog_application, GTK_TYPE_APPLICATION)

ReadinglogApplication *
readinglog_application_new (const char        *application_id,
                            GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (READINGLOG_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     "resource-base-path", "/com/sledgehogsoftware/readinglog",
	                     NULL);
}

static void
readinglog_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (READINGLOG_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (READINGLOG_TYPE_WINDOW,
		                       "application", app,
		                       NULL);

	gtk_window_present (window);
}

static void
readinglog_application_class_init (ReadinglogApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = readinglog_application_activate;
}

static void
readinglog_application_about_action (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer       user_data)
{
	static const char *authors[] = {"Broc", NULL};
	ReadinglogApplication *self = user_data;
	GtkWindow *window = NULL;

	g_assert (READINGLOG_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

	gtk_show_about_dialog (window,
	                       "program-name", "readinglog",
	                       "logo-icon-name", "com.sledgehogsoftware.readinglog",
	                       "authors", authors,
	                       "translator-credits", _("translator-credits"),
	                       "version", "0.1.0",
	                       "copyright", "© 2025 Broc",
	                       NULL);
}

static void
readinglog_application_quit_action (GSimpleAction *action,
                                    GVariant      *parameter,
                                    gpointer       user_data)
{
	ReadinglogApplication *self = user_data;

	g_assert (READINGLOG_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", readinglog_application_quit_action },
	{ "about", readinglog_application_about_action },
};

static void
readinglog_application_init (ReadinglogApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<primary>q", NULL });
}
