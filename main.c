/*
Designed on Glade
compiled on GCC
*/

#include <gtk/gtk.h>
#include <stdbool.h>
#include "DPAS.h"

GtkBuilder *builder;
GtkWidget *total_mem_label, *total_fragment_label;
GUI fifo_gui, best_fit_gui;
Container container;
label fifo_label, best_fit_label;

GtkWidget **fifo_job_display, **fifo_mem_display, **fifo_status_display, **fifo_frag_display;
GtkWidget **best_job_display, **best_mem_display, **best_status_display, **best_frag_display;

data fifo, best_fit;

int main(int argc, char *argv[])
{
    fifo.job_counter = 0;
    fifo.mem_counter = 0;

    best_fit.job_counter = 0;
    best_fit.mem_counter = 0;

    //declares the array of labels to display the output
    fifo_job_display = g_new(GtkWidget *, 5);
    fifo_mem_display = g_new(GtkWidget *, 5);
    fifo_status_display = g_new(GtkWidget *, 5);
    fifo_frag_display = g_new(GtkWidget *, 5);
    
    best_job_display = g_new(GtkWidget *, 5);
    best_mem_display = g_new(GtkWidget *, 5);
    best_status_display = g_new(GtkWidget *, 5);
    best_frag_display = g_new(GtkWidget *, 5);
    
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
    fifo_gui.start = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_start"));
    fifo_gui.clear = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_clear"));

    //fifo label object creation
    fifo_label.entry_label = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_entry_label"));
    fifo_label.mem_entry_label = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_mem_entry_label"));
    fifo_label.status_label = GTK_WIDGET(gtk_builder_get_object(builder, "status_label"));
    fifo_label.internal_fragment_label = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_label"));

    //displays the job size on the FIFO tab
    fifo_job_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_1"));
    fifo_job_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_2"));
    fifo_job_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_3"));
    fifo_job_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_4"));
    fifo_job_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "fifo_job_5"));

    //displays the memory size on the FIFO tab
    fifo_mem_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_1"));
    fifo_mem_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_2"));
    fifo_mem_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_3"));
    fifo_mem_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_4"));
    fifo_mem_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "mem_block_5"));

    //displays the memory block status on the FIFO tab
    fifo_status_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_1"));
    fifo_status_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_2"));
    fifo_status_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_3"));
    fifo_status_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_4"));
    fifo_status_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "status_block_5"));

    //displays the internal fragmentation on first fit tab
    fifo_frag_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_1"));
    fifo_frag_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_2"));
    fifo_frag_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_3"));
    fifo_frag_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_4"));
    fifo_frag_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "fragmentation_5"));

    best_fit_gui.job_entry = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_entry"));
    best_fit_gui.mem_entry = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_entry"));
    best_fit_gui.start =  GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_start"));
    best_fit_gui.clear =  GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_clear"));

    //best fit label object creation
    best_fit_label.entry_label = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_entry_label"));
    best_fit_label.mem_entry_label = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_entry_label"));
    best_fit_label.status_label = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_status_label"));
    best_fit_label.internal_fragment_label = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_fragmentation_label"));

    //displays the job size on best fit tab
    best_job_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_1"));
    best_job_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_2"));
    best_job_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_3"));
    best_job_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_4"));
    best_job_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_job_5"));

    //displays the mem size on best fit tab
    best_mem_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_block_1"));
    best_mem_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_block_2"));
    best_mem_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_block_3"));
    best_mem_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_block_4"));
    best_mem_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_mem_block_5"));

    //displays the status on best fit tab
    best_status_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_status_1"));
    best_status_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_status_2"));
    best_status_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_status_3"));
    best_status_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_status_4"));
    best_status_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fit_status_5"));

    //displays the internal fragmentation on best fit tab
    best_frag_display[0] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fragmentation_1"));
    best_frag_display[1] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fragmentation_2"));
    best_frag_display[2] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fragmentation_3"));
    best_frag_display[3] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fragmentation_4"));
    best_frag_display[4] = GTK_WIDGET(gtk_builder_get_object(builder, "best_fragmentation_5"));


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
    /*
    retrieves the user input and puts them on input variable
    */
    sprintf(input, "Job%d:%s", fifo.job_counter+1, gtk_entry_get_text(job_entry));

    fifo.job_size[fifo.job_counter] = atoi(gtk_entry_get_text(job_entry));

    gtk_label_set_text(GTK_LABEL(fifo_job_display[fifo.job_counter]), (const gchar*) input);
            
    if (fifo.job_counter == 4) 
    {
        gtk_widget_set_sensitive(job_entry, FALSE);
    }

    fifo.job_counter++;
    gtk_entry_set_text(job_entry,"");
}

void fifo_mem_block_entry_activate(GtkEntry *mem_entry)
{
    char input[30];
    
    /*
    retrieves the user input and puts them on input variable
    */
    sprintf(input, "Job%d:%s", fifo.mem_counter+1, gtk_entry_get_text(mem_entry));

    fifo.mem_block[fifo.mem_counter] = atoi(gtk_entry_get_text(mem_entry));
    fifo.is_busy[fifo.mem_counter] = FALSE;

    gtk_label_set_text(GTK_LABEL(fifo_mem_display[fifo.mem_counter]), (const gchar*) input);
    gtk_label_set_text(GTK_LABEL(fifo_status_display[fifo.mem_counter]), (const gchar*) "FREE");

    if (fifo.mem_counter == 4)
    {
        gtk_widget_set_sensitive(mem_entry, FALSE);
    }

    fifo.mem_counter++;
    gtk_entry_set_text(mem_entry,"");
}

//clears the window including the data
void fifo_clear_clicked(GtkButton *clear)
{
    fifo.job_counter = 0;
    fifo.mem_counter = 0;
    for (int i = 0; i < 5; i++)
    {
        gtk_label_set_text(GTK_LABEL(fifo_job_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(fifo_mem_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(fifo_status_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(fifo_frag_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(total_mem_label),(const gchar*) "Total Memory:");
        gtk_label_set_text(GTK_LABEL(total_fragment_label),(const gchar*) "Total Fragmentaion:");

        fifo.job_size[i] = NULL;
        fifo.mem_block[i] = NULL;
    }
    
    gtk_widget_set_sensitive(fifo_gui.start, TRUE);
    gtk_widget_set_sensitive(fifo_gui.job_entry, TRUE);
    gtk_widget_set_sensitive(fifo_gui.mem_entry, TRUE);
}

void fifo_start_clicked(GtkButton *start)
{
    char status[30];
    char fragmentation[10];
    char total_frag[30];
    char total_mem[30];
    fifo.total_fragmentation = 0;
    fifo.total_memory = 0;


    //fifo algo
    for (int i = 0; i < fifo.job_counter; i++)
    {
        sprintf(status, "BUSY(J%d)", i+1);
        for (int j = 0; j < fifo.mem_counter; j++)
        {
            sprintf(fragmentation, "%d", fifo.mem_block[j] - fifo.job_size[i]);
            if (fifo.is_busy[j] == FALSE && fifo.mem_block[j] >= fifo.job_size[i])
            {
                gtk_label_set_text(GTK_LABEL(fifo_status_display[j]), (const gchar*) status);
                gtk_label_set_text(GTK_LABEL(fifo_frag_display[j]), (const gchar*) fragmentation);

                fifo.is_busy[j] = TRUE;
                //gets the total of fragmentation
                fifo.total_fragmentation += (fifo.mem_block[j] - fifo.job_size[i]);
                break;
            }
        }
    }
    
    //gets both the total of memory size
    for (int i = 0; i < fifo.mem_counter; i++)
    {
        fifo.total_memory+= fifo.mem_block[i]; 
    }
    
    sprintf(total_frag, "Total Fragmentation:%d", fifo.total_fragmentation);
    sprintf(total_mem, "Total Memory:%d", fifo.total_memory);

    gtk_label_set_text(GTK_LABEL(total_fragment_label), (const gchar*) total_frag);
    gtk_label_set_text(GTK_LABEL(total_mem_label), (const gchar*) total_mem);

    gtk_widget_set_sensitive(start, FALSE);
    gtk_widget_set_sensitive(fifo_gui.job_entry, FALSE);
    gtk_widget_set_sensitive(fifo_gui.mem_entry, FALSE);
}


void best_fit_job_entry_activate(GtkEntry *job_entry)
{
     char input[30];
    /*
    retrieves the user input and puts them on input variable
    */
    sprintf(input, "Job%d:%s", best_fit.job_counter+1, gtk_entry_get_text(job_entry));

    best_fit.job_size[best_fit.job_counter] = atoi(gtk_entry_get_text(job_entry));

    gtk_label_set_text(GTK_LABEL(best_job_display[best_fit.job_counter]), (const gchar*) input);


    if (best_fit.job_counter == 4) 
    {
        gtk_widget_set_sensitive(job_entry, FALSE);
    }

    best_fit.job_counter++;
    gtk_entry_set_text(job_entry,"");
}


void best_fit_mem_entry_activate(GtkEntry *mem_entry)
{
    char input[30];

    sprintf(input, "Job%d:%s", best_fit.mem_counter+1, gtk_entry_get_text(mem_entry));

    best_fit.mem_block[best_fit.mem_counter] = atoi(gtk_entry_get_text(mem_entry));
    best_fit.is_busy[best_fit.mem_counter] = FALSE;

    gtk_label_set_text(GTK_LABEL(best_mem_display[best_fit.mem_counter]), (const gchar*) input);
    gtk_label_set_text(GTK_LABEL(best_status_display[best_fit.mem_counter]), (const gchar*) "FREE");


    if (best_fit.mem_counter == 4)
    {
        gtk_widget_set_sensitive(mem_entry, FALSE);
    }


    best_fit.mem_counter++;
    gtk_entry_set_text(mem_entry,"");
}

void best_fit_clear_clicked(GtkButton *clear)
{
    best_fit.job_counter = 0;
    best_fit.mem_counter = 0;
    for (int i = 0; i < 5; i++)
    {
        gtk_label_set_text(GTK_LABEL(best_job_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(best_mem_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(best_status_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(best_frag_display[i]),(const gchar*) "");
        gtk_label_set_text(GTK_LABEL(total_mem_label),(const gchar*) "Total Memory:");
        gtk_label_set_text(GTK_LABEL(total_fragment_label),(const gchar*) "Total Fragmentaion:");

        best_fit.job_size[i] = NULL;
        best_fit.mem_block[i] = NULL;
    }
    
    gtk_widget_set_sensitive(best_fit_gui.start, TRUE);
    gtk_widget_set_sensitive(best_fit_gui.job_entry, TRUE);
    gtk_widget_set_sensitive(best_fit_gui.mem_entry, TRUE);
}

void best_fit_start_clicked(GtkButton *start)
{
    char status [30];
    char fragmentation[30];
    char total_frag[30];
    char total_mem[30];
    int best = -1;
    best_fit.total_fragmentation = 0;
    best_fit.total_memory = 0;

    //best fit algo
    for (int i = 0; i < best_fit.job_counter; i++)
    {
        best = -1;
        sprintf(status, "BUSY(J%d)", i+1);
        for (int j = 0; j < best_fit.mem_counter; j++)
        {
            //checks if the block is busy and is greater than the size
            if(best_fit.is_busy[j] == FALSE &&best_fit.mem_block[j] >= best_fit.job_size[i])
            {
                //assigns the index of the lower fragmentation to variable best
                if(best == -1)
                {
                    best = j;
                }
                else if (best_fit.mem_block[best] > best_fit.mem_block[j])
                {
                    best = j;
                }
            }
        }

        //checks if best is not equal to the end of array
        if (best != -1)
        {
            sprintf(fragmentation, "%d", best_fit.mem_block[best] - best_fit.job_size[i]);
            best_fit.total_fragmentation += best_fit.mem_block[best] - best_fit.job_size[i];
            gtk_label_set_text(GTK_LABEL(best_status_display[best]), (const gchar*)status);
            gtk_label_set_text(GTK_LABEL(best_frag_display[best]), (const gchar*) fragmentation);

            best_fit.is_busy[best] = TRUE;
        }
    }
    
    for (int i = 0; i < best_fit.mem_counter; i++)
    {
        //gets the total memory
        best_fit.total_memory += best_fit.mem_block[i];
    }
    
    sprintf(total_frag, "Total Fragmentation:%d", best_fit.total_fragmentation);
    sprintf(total_mem, "Total Memory:%d", best_fit.total_memory);

    gtk_label_set_text(GTK_LABEL(total_fragment_label), (const gchar*) total_frag);
    gtk_label_set_text(GTK_LABEL(total_mem_label), (const gchar*) total_mem);

    gtk_widget_set_sensitive(start, FALSE);
    gtk_widget_set_sensitive(best_fit_gui.job_entry, FALSE);
    gtk_widget_set_sensitive(best_fit_gui.mem_entry, FALSE);
}