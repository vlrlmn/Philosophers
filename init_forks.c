#include "philo.h"

void    init_forks(t_simulation *sim)
{
    int i;
    int ph_counter;

    i = 0;
    ph_counter = sim->sim_params.philosophers;
    sim->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * sim->sim_params.philosophers);
    if(!sim->forks)
        exit_with_error("Failed to allocate memory for forks\n");
    while(i < ph_counter)
    {
        if(pthread_mutex_init(&sim->forks[i], NULL) != 0)
            exit_with_error("Failed to initialize a fork mutex\n");
        i++;
    }
}
