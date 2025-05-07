#include "main-widget.h"
#include "glib.h"
#include "gtk/gtk.h"

struct _MainWidget
{
  GtkWidget parent_instance;

  GtkWidget * label;
  GtkWidget * new_button;
  GtkWidget * open_button;
};

G_DEFINE_TYPE(MainWidget, main_widget, GTK_TYPE_WIDGET)

static void
on_new_button_clicked(GtkButton * button, gpointer user_data)
{
  g_message("New Button pressed.\n");
}

static void
on_open_button_clicked(GtkButton * button, gpointer user_data)
{
  g_message("Open Button pressed.\n");
}

static void
main_widget_init(MainWidget * self)
{
  gtk_widget_init_template(GTK_WIDGET(self));

  g_signal_connect(G_OBJECT(self->new_button), "clicked", G_CALLBACK(on_new_button_clicked), NULL);
  g_signal_connect(G_OBJECT(self->open_button), "clicked", G_CALLBACK(on_open_button_clicked), NULL);
}

static void
main_widget_dispose(GObject * object)
{
  MainWidget * self = MAIN_WIDGET(object);

  // Removes label, buttons (template struct members)
  gtk_widget_dispose_template(GTK_WIDGET(self), MAIN_TYPE_WIDGET);

  // Chain it up
  G_OBJECT_CLASS(main_widget_parent_class)->dispose(object);
}

static void
main_widget_finalize(GObject * object)
{
  MainWidget * self = MAIN_WIDGET(object);

  G_OBJECT_CLASS(main_widget_parent_class)->finalize(object);
}

static void
main_widget_class_init(MainWidgetClass * klass)
{
  GObjectClass * object_class = G_OBJECT_CLASS(klass);
  GtkWidgetClass * widget_class = GTK_WIDGET_CLASS(klass);

  object_class->dispose = main_widget_dispose;
  object_class->finalize = main_widget_finalize;

  gtk_widget_class_set_template_from_resource(widget_class, "/com/sledgehogsoftware/readinglog/main-widget.ui");

  gtk_widget_class_bind_template_child(widget_class, MainWidget, label);
  gtk_widget_class_bind_template_child(widget_class, MainWidget, new_button);
  gtk_widget_class_bind_template_child(widget_class, MainWidget, open_button);
}

GtkWidget *
main_widget_new(void)
{
  return g_object_new(MAIN_TYPE_WIDGET, NULL);
}
