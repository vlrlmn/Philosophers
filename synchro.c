#include "philo.h"

void    wait_all_threads(t_philo_args *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready, table))
        ;
}