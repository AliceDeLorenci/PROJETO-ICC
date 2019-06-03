#include <gtk/gtk.h>


int main(int argc, char* argv[])
{

    gtk_init(&argc,&argv);
    GtkWidget *window1, *label;

    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    label = gtk_label_new("Hello world");

    g_signal_connect(window1,"delete-event",G_CALLBACK(gtk_main_quit),NULL); //quit

    gtk_container_add(GTK_CONTAINER(window1),label); //include label in window

    gtk_widget_show_all(window1);

    gtk_main();

    return 0;

}
