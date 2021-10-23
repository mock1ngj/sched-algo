#include <gtk/gtk.h>

typedef struct
{
    double decimal;
    int integer;
    int counter;
    int process[10];
    int memblock[10];
    char string[200];
}data;

typedef struct
{
    GtkWidget *window;
    GtkWidget *entry_label;
    GtkWidget *fixed_container;
    GtkWidget *fifo_entry;
    GtkWidget *best_fit_entry;
    GtkWidget *fifo_container;
    GtkWidget *best_fit_container;
    GtkWidget *slider;
    GtkWidget *slider_title;
    GtkWidget *slider_label;
    GtkWidget *process_label;
    GtkWidget *process_box;
    GtkWidget *stack;
    GtkWidget *stack_switch_1;
    GtkWidget *stack_switch_2;
    data user_data;
}GUI;

typedef struct
{
    GtkWidget *job_1;
    GtkWidget *job_2;
    GtkWidget *job_3;
    GtkWidget *job_4;
}fifo_jobs;
