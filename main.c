#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit_with_error("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// void destroy_resources(t_simulation *sim) {
//     for (size_t i = 0; i < sim->sim_params.philosophers; ++i) {
//         pthread_mutex_destroy(&sim->forks[i]);
//     }
//     free(sim->forks);
//     free(sim->philosophers);
// }

void init_each_philosopher(t_philo_args *table, int i)
{
    table->philos[i].ph_id = i + 1;
    table->philos[i].meals_eaten = 0;
    table->philos[i].flag = 1;
    table->philos[i].meals_done = 0;
    table->philos[i].right_fork = table->forks[i];
    if (i + 1 == table->ph_amount)
        table->philos[i].left_fork = table->forks[0];
    else
        table->philos[i].left_fork = table->forks[i + 1];
}

void init_philosophers(t_philo_args *table)
{
    int i;

    i = 0;
    table->philos = malloc(sizeof(t_philo) * table->ph_amount);
    if (!table->philos)
    {
        free_forks(table->forks);
        free(table->sim);
        exit_with_error("Memory error: philosopher is not created\n");
    }
    while(i < table->ph_amount)
        init_each_philosopher(table, i++);
}

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

int main(int argc, char **argv)
{
     t_philo_args   table;

    if (argc < 5 || argc > 6)
        exit_with_error("Incorrect amount of arguments\n");
    if (!valid_nums(argv + 1))
        exit_with_error("Invalid arguments\n");
    init_philo_params(&table);
    init_thread(&table);
}