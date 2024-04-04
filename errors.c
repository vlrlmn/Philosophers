/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:23 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/04 14:40:18 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	free_forks(pthread_mutex_t **forks)
{
	int	i;

	i = 0;
	while (forks[i] != NULL)
	{
		pthread_mutex_destroy(forks[i]);
		i++;
	}
	*forks = NULL;
}

void	free_forks_and_exit(pthread_mutex_t **forks, char *msg)
{
	free_forks(forks);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	pthread_failed(char *msg)
{
	printf("%s", msg);
	exit(-1);
}
