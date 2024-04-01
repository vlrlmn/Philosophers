#include "philo.h"

void death_checker(void)
{

}

void philo_routine(void)
{

}

void init_thread(t_philo_args   *table)
{
    pthread_t *threads;
    pthread_t *death_check;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * table->ph_amount);
    if (!threads)
        exit_with_error("Malloc error: failed to create thread\n");
    while(i < table->ph_amount)
        pthread_create(threads + i++, NULL, philo_routine, table);
    i = 0;
    death_check = malloc(sizeof(pthread_t));
    if (!death_check)
        exit_with_error("Malloc error: failed to create death_check\n");
    pthread_create(death_check, NULL, death_checker, table);
    while(i < table->ph_amount)
        pthread_join(threads[i++], NULL);
}