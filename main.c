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
    GtkWidget *vlbl;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *fifobtn;
    GtkWidget *bestfitbtn;
    GtkWidget *vscale;
    GtkWidget *vsclttl;
}GUI;

static void fifoAlgo(GtkWidget *widget, gpointer in)
{
    data *input = in;
    printf("%d\n", input->i);
    input->i++;
}

static void bestFitAlgo(GtkWidget* widget, gpointer in)
{

}

void value_changed(GtkRange *range, gpointer win) 
{
    
   gdouble val = gtk_range_get_value(range);
   gchar *str = g_strdup_printf("%.f", val);    
   gtk_label_set_text(GTK_LABEL(win), str);
   
   g_free(str);
}


int main(int argc, char* argv[])
{
    GtkWidget *vbox, *boxbtn;
    GUI gui;
    data user_data;
    user_data.i = 0;

    gtk_init(&argc, &argv);
	//creates window starts here

    gui.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(gui.window, "Scheduling Algorithm");
    //sets the size of window by 500x500
    gtk_window_set_default_size(gui.window, 700, 700);
    //sets the position on the center of the screen
    gtk_window_set_position(gui.window, GTK_WIN_POS_CENTER_ALWAYS);
	//exit function for the application
    g_signal_connect(gui.window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	
    //ends here

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL , 10);
    boxbtn = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    //creates the slider GUI
    gui.vscale = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL,1, 10, 1);
    gtk_scale_set_draw_value(GTK_SCALE(gui.vscale), FALSE);
    gtk_widget_set_size_request(gui.vscale, -1, 150);
    gui.vlbl = gtk_label_new("");
    gui.vsclttl = gtk_label_new("Number of Processes");
  
    //creates the FIFO button
    gui.fifobtn = gtk_button_new_with_label("FIFO");
    //creates the BEST-FIT button
    gui.bestfitbtn = gtk_button_new_with_label("BEST-FIT");

    //packs the button on boxbtn container
    gtk_box_pack_start(GTK_BOX(boxbtn), gui.fifobtn,FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(boxbtn), gui.bestfitbtn, FALSE, FALSE, 0);

    //packs all the objects in vbox container
    gtk_box_pack_start(GTK_BOX(vbox), gui.vsclttl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), gui.vscale, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), gui.vlbl, FALSE, FALSE, 0);

    //attaches both the boxbtn and hbox container in the grid
    gui.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(gui.window), gui.grid);
    gtk_grid_attach(GTK_GRID(gui.grid), boxbtn, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(gui.grid), vbox, 0, 1, 1, 1);
    gui.entry = gtk_entry_new();

    //handles the signals like mouse click and key presses
    g_signal_connect(G_OBJECT(gui.fifobtn), "clicked", G_CALLBACK(fifoAlgo), &user_data);
    g_signal_connect(G_OBJECT(gui.bestfitbtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(gui.vscale, "value-changed", G_CALLBACK(value_changed), gui.vlbl);      
   
    gtk_widget_show_all(gui.window);
    gtk_main();
    return 0;
}