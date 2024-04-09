/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:29 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/08 19:01:25 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}
