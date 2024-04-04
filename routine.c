#include "philo.h"
long long	get_time_ms(struct timeval start)
{
	struct timeval	now;
	gettimeofday(&now, NULL);

	long long elapsed = (now.tv_sec - start.tv_sec) * 1000LL + (now.tv_usec - start.tv_usec) / 1000LL;
	return elapsed;
}


void *check_if_dead(void *args)
{
    int i;
    int flag;
    t_philo_args *table;

    table = (t_philo_args *)args;
    while(1)
    {
        i = 0;
        while(i < table->ph_amount)
        {
            if(get_time_ms(table->timer) - table->philos[i].last_meal_time > (long long)table->time_to_die)
                change_status(table, "died", i, 1);
            i++;
        }
        flag = 0;
        i = 0;
        while(i < table->ph_amount)
        {
            if(table->philos[i++].meals_eaten >= table->meals_count)
                flag++;
            if(flag == table->ph_amount)
                change_status(table, "philos are full", table->ph_amount - 1, 1);
        }
    }

}

void deadlock_protector(t_philo_args *table, int i)
{
    if((table->ph_amount % 2 == 0) && i % 2 && table->philos[i].flag)
    {
        table->philos[i].flag = 0;
        usleep(100);
        if(i + 1 == table->ph_amount)
            usleep(200);
    }
}

void	usleeper(long long time, struct timeval now)
{
	long long	cur_time;

	cur_time = get_time_ms(now);
	usleep((time - 15) * 1000);
	while (1)
	{
		usleep(50);
		if (get_time_ms(now) >= cur_time + time)
			break ;
	}
}

void	change_status(t_philo_args *table, char *str, int i, int flag)
{
	i++;
	pthread_mutex_lock(table->sim);
	printf("%lld %d %s\n", get_time_ms(table->timer), i, str);
	if (flag)
		exit(42);
	pthread_mutex_unlock(table->sim);
}

void take_forks(t_philo_args *table, pthread_mutex_t *fork1, pthread_mutex_t *fork2, int i)
{
    pthread_mutex_lock(fork1);
	change_status(table, "has taken a fork", i, 0);
	pthread_mutex_lock(fork2);
	change_status(table, "has taken a fork", i, 0);
	table->philos[i].last_meal_time = get_time_ms(table->timer);
	change_status(table, "is eating", i, 0);
	usleeper(table->time_to_eat, table->timer);
	pthread_mutex_unlock(fork2);
	pthread_mutex_unlock(fork1);
	change_status(table, "is sleeping", i, 0);
	usleeper(table->time_to_sleep, table->timer);
	change_status(table, "is thinking", i, 0);
}

void *philo_routine(void *args)
{
    t_philo_args		*table;
	int	i;

	table = (t_philo_args *)args;
	i = table->id++;
    deadlock_protector(table, i);
    while (1)
    {
        if(i % 2)
            take_forks(table, table->philos[i].left_fork, table->philos[i].right_fork, i);
        else
            take_forks(table, table->philos[i].right_fork, table->philos[i].left_fork, i);
        table->philos[i].meals_eaten += 1;
        if(table->philos[i].meals_eaten == table->meals_count)
            table->philos[i].meals_done = 1;
    }
}

/*Init threads and create death flag*/
void init_thread(t_philo_args   *table)
{
    pthread_t *threads;
    pthread_t *dead_flag;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * table->ph_amount);
    if (!threads)
        exit_with_error("Malloc error: failed to create thread\n");
    while(i < table->ph_amount)
        pthread_create(threads + i++, NULL, philo_routine, table);
    i = 0;
    dead_flag = malloc(sizeof(pthread_t));
    if (!dead_flag)
        exit_with_error("Malloc error: failed to create dead flag\n");
    pthread_create(dead_flag, NULL, check_if_dead, table);
    while(i < table->ph_amount)
        pthread_join(threads[i++], NULL);
}
