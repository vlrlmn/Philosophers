/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:26 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/12 20:13:27 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->ph_amount;

	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	init_philosophers(t_philo_args *table)
{
	int	i;
	t_philo *philo;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->ph_amount);
	if (!table->philos)
		exit_with_error("Memory error: philosopher is not created\n");
	while (i < table->ph_amount)
	{
		
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->philo_mutex, NULL))
			exit_with_error("Failed to init mutex\n");
		set_forks(philo, table->forks, i);
		i++;
	}
}

void init_forks(t_philo_args *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(t_philo) * table->ph_amount);
	if (!table->forks)
		exit_with_error("Memory error: fork is not created\n");
	while(i < table->ph_amount)
	{
		if(pthread_mutex_init(&table->forks[i].fork, NULL))
			exit_with_error("Failed to init mutex\n");
		table->forks[i].fork_id = i;
		i++;
	}
}

void	init_table(t_philo_args *table)
{
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_run_num = 0;
	init_forks(table);
	init_philosophers(table);
	if(pthread_mutex_init(&table->table_mutex, NULL))
		exit_with_error("Failed to init mutex\n");
	if(pthread_mutex_init(&table->write_mutex, NULL))
		exit_with_error("Failed to init mutex\n");
}

void	parse_args(t_philo_args *table, char **argv)
{
	table->ph_amount = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		table->meals = ft_atol(argv[5]);
	else
		table->meals = -1;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 
					|| table->time_to_sleep < 6e4)
		exit_with_error("Invalid parameters\n");
}
