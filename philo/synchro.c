/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:52 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/12 19:43:56 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    wait_all_threads(t_philo_args *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready));
}

bool all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
    bool    ret;
    
    ret = false;
    if(pthread_mutex_lock(mutex))
        exit_with_error("Failed to lock mutex\n");
    if (*threads == philo_nbr)
        ret = true;
    if(pthread_mutex_unlock(mutex))
        exit_with_error("Failed to unlock mutex\n");
    return(ret);
}

void increase_long(pthread_mutex_t *mutex, long *value)
{
    if(pthread_mutex_lock(mutex))
       exit_with_error("Failed to lock mutex\n");
    (*value)++;
    if(pthread_mutex_unlock(mutex))
        exit_with_error("Failed to unlock mutex\n");
}

void de_synch(t_philo *philo)
{
    if (philo->table->ph_amount % 2 == 0)
    {
        if (philo->id % 2 == 0)
            precise_usleep(3e4, philo->table);
    }
    else
    {
        if (philo->id % 2)
            think(philo, philo->table, true);
    }
}