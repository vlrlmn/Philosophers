#include "philo.h"

void init_philos(t_simulation *sim)
{
    int i;
    int ph_counter;

    i = 0;
    ph_counter = sim->sim_params.philosophers;
    sim->philosophers = (t_philo_each*)malloc(sizeof(t_philo_each) * sim->sim_params.philosophers);
    if(!sim->philosophers)
        exit_with_error("Failed to initialize a philosopher\n");
    while(i < ph_counter)
    {
        sim->philosophers[i].ph_id = i;
        sim->philosophers[i].meals_eaten = 0;
        sim->philosophers[i].last_meal_time = 0;
        sim->philosophers[i].left_fork = &sim->forks[i];
        sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim->sim_params.philosophers];
        sim->philosophers[i].sim = sim;
        if (pthread_create(&sim->philosophers[i].thread, NULL, &philo_routine, &sim->philosophers[i]) != 0)
                exit_with_error("Failed to create philosopher thread\n");
        i++;
    }
    i = 0;
    while(i < ph_counter)
    {
        pthread_join(sim->philosophers[i].thread, NULL);
        i++;
    }
}

void init_philo_params(t_philo *philo_params, char **argv)
{
    philo_params->start_time = get_time();
    philo_params->philosophers = ft_atol(argv[1]);
    philo_params->time_to_die = ft_atol(argv[2]);
    philo_params->time_to_eat = ft_atol(argv[3]);
    philo_params->time_to_sleep = ft_atol(argv[4]);
    if(argv[5])
    {
        philo_params->meals_count = ft_atol(argv[5]);
        philo_params->has_meals_count = true;
    }
    else
    {
        philo_params->meals_count = 0;
        philo_params->has_meals_count = false;
    }
}
