#include "philo.h"
/*Set parameters for philosophers*/
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

/*Init the philosophers. Malloc for the structure wiht a parameters for each philosopher*/
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

/*Init forks and pfilosophers: malloc memory for mutexes and init them. 
The fork is a shared resource. The philisophers are processes*/
void init_table(t_philo_args *table)
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
        if (!table->forks[i++])
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
    table->start_time = gettimeofday(&table->timer, NULL);
}

/*Init table parameters after parsing*/
void init_table_params(t_philo_args *table, char **argv)
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
