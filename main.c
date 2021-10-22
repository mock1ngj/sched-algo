#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void fifoAlgo(GtkWidget *widget, gpointer data)
{

}

static void button_clicked(GtkWidget *widget, gpointer data)
{
    int memSize[5] = {300, 200, 100, 500, 780};
    int input[5], j;
    
    input[j] = atoi(gtk_entry_get_text(GTK_ENTRY(data)));

    if ((memSize[j] - input[j]) >= 0)
    {
        printf("Allocated at block %d with %d of internal fragmentation\n", j, memSize[j]-input[j]);
    }
    j++;
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *window, *menubox, *fifo, *bestfit;
    GtkWidget *menuBar, *grid, *entry, *box;

	//creates window starts here

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(window, "Scheduling Algorithm");
    //sets the size of window by 500x500
    gtk_window_set_default_size(window, 700, 700);
    //sets the position on the center of the screen
    gtk_window_set_position(window, GTK_WIN_POS_CENTER_ALWAYS);
	//exit function for the application
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	
    //ends here


    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();

    /*menu creation starts here
    creates a box for the menu
    */
    menubox = gtk_vbox_new(FALSE, 0);

    //creates a new menuBar object
    menuBar = gtk_menu_bar_new();
    //creates a new menu object

    //creates the labels for the menu objeect
    fifo = gtk_menu_item_new_with_label("FIFO");
    bestfit = gtk_menu_item_new_with_label("BEST-FIT");

    //assigns the label to the menuBar object
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), bestfit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), fifo);
    gtk_box_pack_start(GTK_BOX(menubox), menuBar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(fifo), "activate", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(bestfit), "activate", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(entry, "activate", G_CALLBACK(button_clicked), entry);
   
    //ends here
    gtk_grid_attach(GTK_GRID(grid), menubox, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 1, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}