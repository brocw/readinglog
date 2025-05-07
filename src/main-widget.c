#include "main-widget.h"
#include "gtk/gtk.h"

struct _MainWidget
{
  GtkWidget parent_instance;

  GtkWidget * label;
  GtkWidget * button;
};

G_DEFINE_TYPE(MainWidget, main_widget, GTK_TYPE_WIDGET)

static void
main_widget_init(MainWidget * self)
{
  gtk_widget_init_template(GTK_WIDGET(self));
}

static void
main_widget_dispose(GObject * object)
{
  MainWidget * self = MAIN_WIDGET(object);

  // Removes label, button (template struct members)
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
  gtk_widget_class_bind_template_child(widget_class, MainWidget, button);
}

GtkWidget *
main_widget_new(void)
{
  return g_object_new(MAIN_TYPE_WIDGET, NULL);
}
