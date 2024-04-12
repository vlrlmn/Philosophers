/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:29 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/12 20:08:00 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_table(t_philo_args *table)
{
	t_philo *philo;
	int i;

	i = 0;
	while(i < table->ph_amount)
	{
		philo = table->philos + i;
		i++;
		if(pthread_mutex_destroy(&philo->philo_mutex))
			exit_with_error("Error destroying mutex\n");
	}
	if(pthread_mutex_destroy(&table->write_mutex))
		exit_with_error("Error destroying mutex\n");
	if(pthread_mutex_destroy(&table->table_mutex))
		exit_with_error("Error destroying mutex\n");
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_philo_args	table;

	if (argc < 5 || argc > 6)
		exit_with_error("Incorrect amount of arguments\n");
	if (!valid_nums(argv + 1))
		exit_with_error("Invalid arguments\n");
	parse_args(&table, argv);
	init_table(&table);
	init_thread(&table);
	clean_table(&table);
}
