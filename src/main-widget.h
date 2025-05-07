#pragma once

#include "glib-object.h"
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MAIN_TYPE_WIDGET main_widget_get_type()
G_DECLARE_FINAL_TYPE(MainWidget, main_widget, MAIN, WIDGET, GtkWidget)

GtkWidget * main_widget_new(void);

G_END_DECLS
