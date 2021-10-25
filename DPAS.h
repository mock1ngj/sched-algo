#include <gtk/gtk.h>
#include <stdbool.h>
/*declares all the necessary objects and stores 
them in a struct for readability and easy access
on main
*/
typedef struct
{
    GtkWidget *job_entry;
    GtkWidget *mem_entry;
    GtkWidget *stack_switch_1;
    GtkWidget *stack_switch_2;
    GtkWidget *start;
    GtkWidget *clear;
}GUI;

typedef struct
{
    GtkWidget *window;
    GtkWidget *best_fit_container;
    GtkWidget *fixed_container;
    GtkWidget *fifo_container;
    GtkWidget *stack;
}Container;

typedef struct
{
    GtkWidget *entry_label;
    GtkWidget *mem_entry_label;
    GtkWidget *status_label;
    GtkWidget *internal_fragment_label;
}label;

typedef struct
{
    int job_size[5];
    int job_counter;
    int mem_block[5];
    int mem_counter;
    int total_fragmentation;
    int total_memory;
    bool is_busy[5];
}data;