/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:37 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/09 13:41:10 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void eat(t_philo *philo, t_philo_args *table)
{
	if(pthread_mutex_lock(&philo->first_fork->fork))
        error_mutex("Mutex lock err\n", table);
	write_status(TAKE_FIRST_FORK, philo, table);
	if(pthread_mutex_lock(&philo->second_fork->fork))
        error_mutex("Mutex unlock err\n", table);
	write_status(TAKE_SECOND_FORK, philo, table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND, table), table);
	philo->meals_counter++;
	write_status(EATING, philo, table);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals > 0 && philo->meals_counter == philo->table->meals)
		set_bool(&philo->philo_mutex, &philo->full, true, table);
	if(pthread_mutex_unlock(&philo->first_fork->fork))
        error_mutex("Mutex lock err\n", table);
	if(pthread_mutex_unlock(&philo->second_fork->fork))
        error_mutex("Mutex lock err\n", table);

}

void *philo_routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	
	wait_all_threads(philo->table);
	while(!sim_finished(philo->table))
	{
		if(philo->full)
			break ;
		eat(philo, philo->table);
		write_status(SLEEPING, philo, philo->table);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
}

void join_threads(t_philo_args *table)
{
	int i;

	i = 0;
	while(i < table->ph_amount)
	{
		if(pthread_join(&table->philos[i].thread_id, NULL))
			pthread_failed("Failed to join threads\n", table);
		i++;
	}
}

void init_thread(t_philo_args *table)
{
	int i;

	i = 0;
	if (table->meals == 0)
		return ;
	else if(table->ph_amount == 1)
		;
	else
	{
		while(i < table->ph_amount)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &table->philos[i]))
				pthread_failed("Failed to create thread", table);
			i++;
		}
	}
	table->start_sim = gettime(MILLISECOND, table);
	set_bool(&table->table_mutex, table->all_threads_ready, true, table);
	join_threads(table);
}