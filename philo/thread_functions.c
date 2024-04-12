/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:03:51 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/12 20:06:22 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo, t_philo_args *table, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if(!pre_sim)
		write_status(THINKING, philo, table);
	write_status(THINKING, philo, table);
	if (philo->table->ph_amount % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.4, philo->table);
}

static void eat(t_philo *philo, t_philo_args *table)
{
	if(pthread_mutex_lock(&philo->first_fork->fork))
        exit_with_error("Mutex lock error\n");
	write_status(TAKE_FIRST_FORK, philo, table);
	if(pthread_mutex_lock(&philo->second_fork->fork))
        exit_with_error("Mutex lock error\n");
	write_status(TAKE_SECOND_FORK, philo, table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, table);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals > 0 && philo->meals_counter == philo->table->meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	if(pthread_mutex_unlock(&philo->first_fork->fork))
        exit_with_error("Mutex unlock error\n");
	if(pthread_mutex_unlock(&philo->second_fork->fork))
    	exit_with_error("Mutex unlock error\n");
}

void *one_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->threads_run_num);
	write_status(TAKE_FIRST_FORK, philo, philo->table);
	while(!sim_finished(philo->table))
		usleep(200);
	return(NULL);
}

void *philo_routine(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->threads_run_num);
	de_synch(philo);
	while(!sim_finished(philo->table))
	{
		if(get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo, philo->table);
		write_status(SLEEPING, philo, philo->table);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, philo->table, false);
	}
	return (NULL);
}
