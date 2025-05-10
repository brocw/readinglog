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

#include "config.h"
#include "main-widget.h"
#include "readinglog-window.h"

struct _ReadinglogWindow
{
	GtkApplicationWindow  parent_instance;

	/* Template widgets */
	GtkWidget            *main;
};

G_DEFINE_FINAL_TYPE (ReadinglogWindow, readinglog_window, GTK_TYPE_APPLICATION_WINDOW)

static void
new_selected(MainWidget * main, gpointer user_data)
{
	g_message("New signal recieved\n");
}

static void
open_selected(GFile * file, gpointer user_data)
{
	g_message("Open signal recieved\n");
}

static void
readinglog_window_class_init (ReadinglogWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	g_type_ensure(MAIN_TYPE_WIDGET);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/sledgehogsoftware/readinglog/readinglog-window.ui");
	gtk_widget_class_bind_template_child (widget_class, ReadinglogWindow, main);
}

static void
readinglog_window_init (ReadinglogWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
	g_signal_connect(self->main, "main_new", G_CALLBACK(new_selected), NULL);
	g_signal_connect(self->main, "main_open", G_CALLBACK(open_selected), NULL);
}
