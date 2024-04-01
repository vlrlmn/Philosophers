#include "philo.h"

void init_philo_params(t_philo_args *table)
{
    int i;

    i = 0;
    table->id = 0;
    table->forks = malloc(sizeof(pthread_mutex_t *) * table->ph_amount);
    if (!table->forks)
        exit_with_error("Error to malloc memory for forks \n");
    while(i < table->ph_amount)
    {
        table->forks[i] = malloc(sizeof(pthread_mutex_t));
        if (!table->forks[i++]);
            free_forks_and_exit(table->forks, "Error to malloc memory\n");
    }
    i = 0;
    while(i < table->ph_amount)
        pthread_mutex_init(table->forks[i++], NULL);
    table->sim = malloc(sizeof(pthread_mutex_t));
    if (!table->sim)
        free_forks_and_exit(table->forks, "Error to malloc memory\n");
    pthread_mutex_init(table->sim, NULL);
    init_philosophers(table);
    table->start_time = get_time();
}

void init_philo_params(t_philo_args *table, char **argv)
{
    table->ph_amount = ft_atol(argv[1]);
    table->time_to_die = ft_atol(argv[2]);
    table->time_to_eat = ft_atol(argv[3]);
    table->time_to_sleep = ft_atol(argv[4]);
    if(argv[5])
        table->meals_count = ft_atol(argv[5]);
  
    else
        table->meals_count = 0;
    if (table->ph_amount < 2)
        exit_with_error("Invalid amount of philosophers\n");
}
