/*
Designed on Glade
compiled on GCC
*/

#include <gtk/gtk.h>
#include <stdlib.h>
#include "DPAS.h"

GtkBuilder *builder;
GtkWidget *total_mem_label, *total_fragment_label;
GUI fifo_gui, best_fit_gui;
Container container;
label fifo_label, best_fit_label;

int job_size[5], mem_size[5], fragmentation[5];
int total_fragmentation, total_memory;

int main(int argc, char *argv[])
{
    fifo_label.job_label.counter = 0;
    fifo_label.mem_label.counter = 0;
    total_fragmentation = 0;
    total_memory = 0;
    //starts the gtk loop
    gtk_init(&argc, &argv);

    /*builder object that gets the layout from a .glade file
    which is really just an XML file that stores all the
    info of all the objects
    */
    builder = gtk_builder_new_from_file("DPAS.glade");
    //creates the window
    container.window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    //to be able to exit the window
    g_signal_connect(container.window,"destroy", G_CALLBACK(gtk_main_quit), NULL);

    //connects all the signals to their respective objects
    gtk_builder_connect_signals(builder, NULL);

    //creates the container
    container.fixed_container = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_container"));
    container.stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
    
    container.fifo_container = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_container"));
    container.best_fit_container = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_container"));
    
    //switch for page 1 on the stack container
    fifo_gui.stack_switch_1 = GTK_WIDGET(gtk_builder_get_object(builder, "stack_switch_1"));
    //switch for page 1 on the stack container
    best_fit_gui.stack_switch_2 = GTK_WIDGET(gtk_builder_get_object(builder, "stack_switch_2"));
    
    total_mem_label = GTK_WIDGET(gtk_builder_get_object(builder, "total_memory"));
    total_fragment_label = GTK_WIDGET(gtk_builder_get_object(builder, "total_fragmentation"));

    //creates the entry for FIFO
    fifo_gui.job_entry = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_entry"));
    fifo_gui.mem_entry = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_mem_lock_entry"));
    fifo_gui.button = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_start"));

    //fifo label object creation
    fifo_label.entry_label = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_entry_label"));
    fifo_label.mem_entry_label = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_mem_entry_label"));
    fifo_label.status_label = GTK_WIDGET(gtk_builder_get_object(builder, "status_label"));
    fifo_label.internal_fragment_label = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_label"));

    //displays the job size
    fifo_label.job_label.job_1 = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_1"));
    fifo_label.job_label.job_2 = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_2"));
    fifo_label.job_label.job_3 = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_3"));
    fifo_label.job_label.job_4 = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_4"));
    fifo_label.job_label.job_5 = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_5"));

    //displays the memory size
    fifo_label.mem_label.mem_block_1 = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_1"));
    fifo_label.mem_label.mem_block_2 = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_2"));
    fifo_label.mem_label.mem_block_3 = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_3"));
    fifo_label.mem_label.mem_block_4 = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_4"));
    fifo_label.mem_label.mem_block_5 = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_5"));

    //displays the memory block status
    fifo_label.status.block_1 = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_1"));
    fifo_label.status.block_2 = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_2"));
    fifo_label.status.block_3 = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_3"));
    fifo_label.status.block_4 = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_4"));
    fifo_label.status.block_5 = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_5"));

    fifo_label.internal_fragment.block_1 = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_1"));
    fifo_label.internal_fragment.block_2 = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_2"));
    fifo_label.internal_fragment.block_3 = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_3"));
    fifo_label.internal_fragment.block_4 = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_4"));
    fifo_label.internal_fragment.block_5 = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_5"));

    best_fit_gui.job_entry = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_entry"));
    best_fit_label.entry_label =  GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_entry_label"));

    //to be able to see the different widgets/objects
    gtk_widget_show_all(container.window);

    //main loop for the GTK
    gtk_main();
    return EXIT_SUCCESS;
}

/*
gets the user input and displays them on their respective holder
*/
void fifo_job_entry_activate(GtkEntry *job_entry)
{
    char input[30];
        
    if (fifo_label.job_label.counter == 5)
    {
        fifo_label.job_label.counter = 0;
    }
    /*
    retrieves the user input and puts them on input variable
    */
    sprintf(input, "Job%d:%s", fifo_label.job_label.counter+1, gtk_entry_get_text(job_entry));

    job_size[fifo_label.job_label.counter] = atoi(gtk_entry_get_text(job_entry));
    fifo_label.job_label.counter++;

    switch (fifo_label.job_label.counter)
    {
        case 1:
            gtk_label_set_text(GTK_LABEL(fifo_label.job_label.job_1), (const gchar*) input);
        break;
        
        case 2:
            gtk_label_set_text(GTK_LABEL(fifo_label.job_label.job_2), (const gchar*) input);
        break;

        case 3:
            gtk_label_set_text(GTK_LABEL(fifo_label.job_label.job_3), (const gchar*) input);
        break;

        case 4:
            gtk_label_set_text(GTK_LABEL(fifo_label.job_label.job_4), (const gchar*) input);
        break;

        case 5:
            gtk_label_set_text(GTK_LABEL(fifo_label.job_label.job_5), (const gchar*) input);
        break;
    }
   gtk_entry_set_text(job_entry,"");
}

void fifo_mem_block_entry_activate(GtkEntry *mem_entry)
{
    char input[30];
        
    if (fifo_label.mem_label.counter == 5)
    {
        fifo_label.mem_label.counter = 0;
    }
    /*
    retrieves the user input and puts them on input variable
    */
    sprintf(input, "Job%d:%s", fifo_label.mem_label.counter+1, gtk_entry_get_text(mem_entry));

    mem_size[fifo_label.mem_label.counter] = atoi(gtk_entry_get_text(mem_entry));
    fifo_label.mem_label.counter++;

    switch (fifo_label.mem_label.counter)
    {
        case 1:
            gtk_label_set_text(GTK_LABEL(fifo_label.mem_label.mem_block_1), (const gchar*) input);
            gtk_label_set_text(GTK_LABEL(fifo_label.status.block_1), (const gchar*) "FREE");
        break;
        
        case 2:
            gtk_label_set_text(GTK_LABEL(fifo_label.mem_label.mem_block_2), (const gchar*) input);
            gtk_label_set_text(GTK_LABEL(fifo_label.status.block_2), (const gchar*) "FREE");
        break;

        case 3:
            gtk_label_set_text(GTK_LABEL(fifo_label.mem_label.mem_block_3), (const gchar*) input);
            gtk_label_set_text(GTK_LABEL(fifo_label.status.block_3), (const gchar*) "FREE");
        break;

        case 4:
            gtk_label_set_text(GTK_LABEL(fifo_label.mem_label.mem_block_4), (const gchar*) input);
            gtk_label_set_text(GTK_LABEL(fifo_label.status.block_4), (const gchar*) "FREE");
        break;

        case 5:
            gtk_label_set_text(GTK_LABEL(fifo_label.mem_label.mem_block_5), (const gchar*) input);
            gtk_label_set_text(GTK_LABEL(fifo_label.status.block_5), (const gchar*) "FREE");
        break;
    }
    gtk_entry_set_text(mem_entry,"");
}

void fifo_start_clicked(GtkButton *start)
{
    char status[30];
    char fragmentation[10];
    char total_frag[30];
    char total_mem[30];

    //fifo algo
    for (int i = 0; i < fifo_label.job_label.counter; i++)
    {
        sprintf(status, "BUSY(J%d)", i+1);
        for (int j = i; j < fifo_label.mem_label.counter; j++)
        {
            sprintf(fragmentation, "%d", mem_size[j] - job_size[i]);
            if ((mem_size[j] - job_size[i]) >= 0)
            {
                switch (j)
                {
                    case 0:
                        gtk_label_set_text(GTK_LABEL(fifo_label.status.block_1), (const gchar*) status);
                        gtk_label_set_text(GTK_LABEL(fifo_label.internal_fragment.block_1), (const gchar*) fragmentation);
                    break;
        
                    case 1:
                        gtk_label_set_text(GTK_LABEL(fifo_label.status.block_2), (const gchar*) status);
                         gtk_label_set_text(GTK_LABEL(fifo_label.internal_fragment.block_2), (const gchar*) fragmentation);
                    break;

                    case 2:
                        gtk_label_set_text(GTK_LABEL(fifo_label.status.block_3), (const gchar*) status);
                        gtk_label_set_text(GTK_LABEL(fifo_label.internal_fragment.block_3), (const gchar*) fragmentation);
                    break;

                    case 3:
                        gtk_label_set_text(GTK_LABEL(fifo_label.status.block_4), (const gchar*) status);
                        gtk_label_set_text(GTK_LABEL(fifo_label.internal_fragment.block_4), (const gchar*) fragmentation);
                    break;

                    case 4:
                        gtk_label_set_text(GTK_LABEL(fifo_label.status.block_5), (const gchar*) status);
                        gtk_label_set_text(GTK_LABEL(fifo_label.internal_fragment.block_5), (const gchar*) fragmentation);
                    break;
                }
                //gets the total of fragmentation
                total_fragmentation += (mem_size[j]-job_size[i]);      
                break;
            }
        }

        //gets both the total of memory size
        total_memory+= mem_size[i]; 
    }
    
    sprintf(total_frag, "Total Fragmentation:%d", total_fragmentation);
    sprintf(total_mem, "Total Memory:%d", total_memory);
    gtk_label_set_text(GTK_LABEL(total_fragment_label), (const gchar*) total_frag);
    gtk_label_set_text(GTK_LABEL(total_mem_label), (const gchar*) total_mem);
}

void best_fit_job_entry_activate(GtkEntry *job_entry)
{

}