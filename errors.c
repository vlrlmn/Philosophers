/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:23 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/10 17:21:11 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	free_philos(t_philo_args *table)
{
	int	i;

	i = 0;
	while (table->forks)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	free(table->forks);
}
void	free_forks(t_philo_args *table)
{
	int	i;

	i = 0;
	while (table->forks)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	free(table->forks);
}

void	free_forks_and_exit(t_philo_args *table, char *msg)
{
	(void)table;
	//free_forks(table);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	pthread_failed(char *msg, t_philo_args *table)
{
	(void)table;
	//free_forks(table);
	//free_philos(table);
	printf("%s", msg);
	exit(-1);
}

void  error_mutex(char *msg, t_philo_args *table)
{
	(void)table;
	//free_forks(table);
	//free_philos(table);
	printf("%s", msg);
	exit(-1);
}

void  time_err(char *msg, t_philo_args *table)
{
	(void)table;
	//free_forks(table);
	//free_philos(table);
	printf("%s", msg);
	exit(-1);
};