#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct
{
    int i;
}data;

typedef struct
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *grid;
    GtkWidget *entry;
    
}Widget;

void value_changed(GtkRange *range, gpointer win) 
{
    
   gdouble val = gtk_range_get_value(range);
   gchar *str = g_strdup_printf("%.f", val);    
   gtk_label_set_text(GTK_LABEL(win), str);
   
   g_free(str);
}
static void fifoAlgo(GtkWidget *widget, gpointer in)
{
    data *input = in;
    printf("%d\n", input->i);
    input->i++;
}

static void button_click(GtkWidget *widget, gpointer user_data)
{
    int in;
    in = atoi(gtk_entry_get_text(GTK_ENTRY(user_data)));
    printf("%d\n", in);
}

static void button_clicked(GtkWidget *widget, gpointer data)
{
    Widget* input=(Widget*) data;
    g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(input->entry)));
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *fifo, *bestfit;
    Widget widget;
    data user_data;
    user_data.i = 0;
	//creates window starts here

    widget.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(widget.window, "Scheduling Algorithm");
    //sets the size of window by 500x500
    gtk_window_set_default_size(widget.window, 700, 700);
    //sets the position on the center of the screen
    gtk_window_set_position(widget.window, GTK_WIN_POS_CENTER_ALWAYS);
	//exit function for the application
    g_signal_connect(widget.window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	
    //ends here


    widget.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(widget.window), widget.grid);

    widget.entry = gtk_entry_new();

    //creates the FIFO button
    fifo = gtk_button_new_with_label("FIFO");
    gtk_widget_set_size_request(fifo, 70, 30);
    gtk_grid_attach(GTK_GRID(widget.grid), fifo, 0, 0, 1, 1);
    //creates the BEST-FIT button
    bestfit = gtk_button_new_with_label("BEST-FIT");
    gtk_widget_set_size_request(bestfit, 70, 30);
    gtk_grid_attach(GTK_GRID(widget.grid), bestfit, 1, 0, 1, 1);

    g_signal_connect(G_OBJECT(fifo), "clicked", G_CALLBACK(fifoAlgo), &user_data);
    g_signal_connect(G_OBJECT(bestfit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(widget.entry, "activate", G_CALLBACK(button_clicked), &widget);

   
    //ends here

    gtk_widget_show_all(widget.window);
    gtk_main();
    return 0;
}