/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_agrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:04:00 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/04 13:18:42 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_num(char *argv)
{
	int	i;

	i = 0;
	if ((argv[i] == '-' || argv[i] == '+') && !argv[i + 1])
		return (0);
	if (argv[i] == '-' || argv[i] == '+')
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	valid_nums(char **argv)
{
	int	i;

	i = 0;
	if (!argv || !*argv)
		return (false);
	while (argv[i] && i < 4)
	{
		if (!is_num(argv[i]) || atol(argv[i]) <= 0)
			return (false);
		i++;
	}
	if (argv[4] && (!is_num(argv[4]) || atol(argv[4]) < 0))
		return (false);
	return (true);
}
