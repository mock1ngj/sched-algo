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
    GtkWidget *button;
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
    GtkWidget *job_1;
    GtkWidget *job_2;
    GtkWidget *job_3;
    GtkWidget *job_4;
    GtkWidget *job_5;
    int counter;
}Jobs;


typedef struct
{
    GtkWidget *mem_block_1;
    GtkWidget *mem_block_2;
    GtkWidget *mem_block_3;
    GtkWidget *mem_block_4;
    GtkWidget *mem_block_5;
    int counter;
}Mem;

typedef struct
{
    GtkWidget *block_1;
    GtkWidget *block_2;
    GtkWidget *block_3;
    GtkWidget *block_4;
    GtkWidget *block_5;
}Status_Label;

typedef struct
{
    GtkWidget *block_1;
    GtkWidget *block_2;
    GtkWidget *block_3;
    GtkWidget *block_4;
    GtkWidget *block_5;
}Internal_Fragment_Label;

typedef struct
{
    GtkWidget *entry_label;
    GtkWidget *mem_entry_label;
    Mem mem_label;
    Jobs job_label;
    GtkWidget *status_label;
    Status_Label status;
    GtkWidget *internal_fragment_label;
    Internal_Fragment_Label internal_fragment;
}label;

typedef struct
{
    int job_size[5];
    int mem_block[5];
    bool is_busy[5];
}data;