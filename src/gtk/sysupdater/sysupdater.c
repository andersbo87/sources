/*
This is supposed to be a graphical tool which can be used to update
a user's FreeBSD base system (I do have a feeling I'm in deep water here…).
*/

#include <gtk/gtk.h>

void lookForUpdates(GtkWidget *widget, gpointer data)
{
  /*
    Dette er stedet hvor søket etter oppdateringer vil finne sted.
   */
  g_print("Dette er stedet hvor søket etter oppdateringer vil finne sted.");
}

void on_window_destroy(GtkObject *object, gpointer user_data)
{
  gtk_main_quit();
}
/*main-metoden er lik i alle C og C++-programmer.*/
int main(int argc, char **argv)
{
  GtkBuilder *builder;
  GtkWidget  *window;
  gtk_init(&argc, &argv);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "/usr/home/andersbo/prosjekt1_glade.glade", NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, window));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(G_OBJECT(builder));
  gtk_widget_show(window);
  gtk_main();
  return 0;
}
