/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:52 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/10 14:34:48 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    wait_all_threads(t_philo_args *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready, table))
        ;
}

bool all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr, t_philo_args *table)
{
    bool    ret;
    
    ret = false;
    if(pthread_mutex_lock(mutex))
        error_mutex("Mutex lock err\n", table);
    if (*threads == philo_nbr)
        ret = true;
    if(pthread_mutex_unlock(mutex))
        error_mutex("Mutex unlock err\n", table);
    return(ret);
}

void increase_long(pthread_mutex_t *mutex, long *value, t_philo_args *table)
{
    if(pthread_mutex_lock(mutex))
        error_mutex("Mutex lock err\n", table);
    (*value)++;
    if(pthread_mutex_unlock(mutex))
        error_mutex("Mutex unlock err\n", table);
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
            thinking(philo);
    }
}