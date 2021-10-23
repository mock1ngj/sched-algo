#include <gtk/gtk.h>
#include "DPAS.h"

GtkBuilder *builder, *entry_title, *entry_title_2;
GUI gui;
fifo_jobs fifo;
int counter = 0;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("DPAS.glade");
    gui.window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(gui.window,"destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    gui.fixed_container = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_container"));
    gui.stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
    gui.fifo_container = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_container"));
    gui.best_fit_container = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_container"));
    gui.stack_switch_1 = GTK_WIDGET(gtk_builder_get_object(builder, "stack_switch_1"));
    gui.stack_switch_2 = GTK_WIDGET(gtk_builder_get_object(builder, "stack_switch_2"));
    gui.fifo_entry = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_entry"));
    entry_title = GTK_WIDGET(gtk_builder_get_object(builder, "entry_title"));
    entry_title_2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_title_2"));
    fifo.job_1 = GTK_WIDGET(gtk_builder_get_object(builder, "job_1"));
    fifo.job_2 = GTK_WIDGET(gtk_builder_get_object(builder, "job_2"));
    fifo.job_3 = GTK_WIDGET(gtk_builder_get_object(builder, "job_3"));
    fifo.job_4 = GTK_WIDGET(gtk_builder_get_object(builder, "job_4"));

    gtk_widget_show_all(gui.window);

    gtk_main();
    return EXIT_SUCCESS;
}

void fifo_entry_activate(GtkEntry *e)
{
    char test [30];
    sprintf(test, "Job%d:%d", counter+1,atoi(gtk_entry_get_text(e)));
    counter++;
    g_print("%d", counter);

    switch (counter)
    {
        case 1:
            gtk_label_set_text(GTK_LABEL(fifo.job_1), (const gchar*) test);
        break;
        
        case 2:
            gtk_label_set_text(GTK_LABEL(fifo.job_2), (const gchar*) test);
        break;

        case 3:
            gtk_label_set_text(GTK_LABEL(fifo.job_3), (const gchar*) test);
        break;

        case 4:
            gtk_label_set_text(GTK_LABEL(fifo.job_4), (const gchar*) test);
        break;
    }
}

