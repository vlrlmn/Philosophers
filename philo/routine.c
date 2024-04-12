/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:37 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/12 20:05:44 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void join_threads(t_philo_args *table)
{
	int i;

	i = 0;
	while(i < table->ph_amount)
	{
		if(pthread_join(table->philos[i].thread_id, NULL))
			exit_with_error("Failed to join threads\n");
		i++;
	}
}

void create_threads(t_philo_args *table)
{
	int i;

	i = 0;
	if(table->ph_amount == 1)
	{
		if (pthread_create(&table->philos[0].thread_id, NULL, one_philo, &table->philos[0]))
				exit_with_error("Failed to create thread\n");
	}
	else
	{
		while(i < table->ph_amount)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &table->philos[i]))
				exit_with_error("Failed to create thread\n");
			i++;
		}
	}

}

void init_thread(t_philo_args *table)
{
	if (table->meals == 0)
		return ;
	else
		create_threads(table);
	if(pthread_create(&table->monitor, NULL, monitor_dinner, table))
		exit_with_error("Failed to create thread\n");
	table->start_sim = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	join_threads(table);
	set_bool(&table->table_mutex, &table->end_sim, true);
	if(pthread_join(table->monitor, NULL))
		exit_with_error("Failed to join thread\n");
}