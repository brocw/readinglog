#include "main-widget.h"
#include "gio/gio.h"
#include "glib.h"
#include "gtk/gtk.h"

enum signal_types {
  MAIN_NEW,
  MAIN_OPEN,
  LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

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
  g_signal_emit(MAIN_WIDGET(user_data), signals[MAIN_NEW], 0);
}

static gboolean
abort_opening_file(gpointer data)
{
  GCancellable * cancellable = data;
  g_cancellable_cancel(cancellable);
  return G_SOURCE_REMOVE;
}

static void
set_file(GFile * file, gpointer data)
{
  GFileInfo * info;
  char * name;

  if (!file) {
    g_object_set_data(G_OBJECT(data), "file", NULL);
    return;
  }

  name = g_file_get_basename(file);
  g_message("File opened: %s\n", name);
  g_free(name);

  info = g_file_query_info(file, "standard::content-type", 0, NULL, NULL);
  g_message("File ending: %s\n", g_file_info_get_content_type(info));
  g_signal_emit(G_FILE(file), signals[MAIN_OPEN], 0);
}

static void
file_opened(GObject * source, GAsyncResult * result, void * data)
{
  GFile * file;
  GError * error = NULL;

  file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, &error);

  if (!file) {
    g_message("File opened: %s\n", error->message);
    g_error_free(error);
    g_object_set_data(G_OBJECT(data), "file", NULL);
  } else {
    set_file(file, data);
  }
}

static void
on_open_button_clicked(GtkButton * button, gpointer user_data)
{
  GtkWindow * parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));
  GtkFileDialog * dialog;
  GCancellable * cancellable;

  dialog = gtk_file_dialog_new();
  cancellable = g_cancellable_new();

  g_timeout_add_seconds_full(G_PRIORITY_DEFAULT, 20, abort_opening_file, g_object_ref(cancellable), g_object_unref);

  gtk_file_dialog_open(dialog, parent, cancellable, file_opened, user_data);

  g_object_unref(cancellable);
  g_object_unref(dialog);
}

static void
main_widget_init(MainWidget * self)
{
  gtk_widget_init_template(GTK_WIDGET(self));

  g_signal_connect(G_OBJECT(self->new_button), "clicked", G_CALLBACK(on_new_button_clicked), self);
  g_signal_connect(G_OBJECT(self->open_button), "clicked", G_CALLBACK(on_open_button_clicked), self->open_button);
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

  signals[MAIN_OPEN] = g_signal_new_class_handler("main_open", G_OBJECT_CLASS_TYPE(object_class), G_SIGNAL_RUN_LAST,
                                                  NULL, NULL, NULL, NULL, G_TYPE_NONE, 0); 
  signals[MAIN_NEW] = g_signal_new_class_handler("main_new", G_OBJECT_CLASS_TYPE(object_class), G_SIGNAL_RUN_LAST,
                                                  NULL, NULL, NULL, NULL, G_TYPE_NONE, 0); 
}

GtkWidget *
main_widget_new(void)
{
  return g_object_new(MAIN_TYPE_WIDGET, NULL);
}
