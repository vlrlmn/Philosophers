/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:01:25 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/10 14:01:26 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_bool(pthread_mutex_t *mutex, bool *dest, bool value, t_philo_args *table)
{
    if(pthread_mutex_lock(mutex))
        error_mutex("Mutex lock err\n", table);
    *dest = value;
    if(pthread_mutex_unlock(mutex))
        error_mutex("Mutex unlock err\n", table);
}

bool get_bool(pthread_mutex_t *mutex, bool *value, t_philo_args *table)
{
    bool    ret;
    if(pthread_mutex_lock(mutex))
        error_mutex("Mutex lock err\n", table);
    ret = *value;
    if(pthread_mutex_unlock(mutex))
        error_mutex("Mutex unlock err\n", table);
    return(ret);
}

/*LONG*/
long get_long(pthread_mutex_t *mutex, long *value, t_philo_args *table)
{
    long    ret;
    if(pthread_mutex_lock(mutex))
        error_mutex("Mutex lock err\n", table);
    ret = *value;
    if(pthread_mutex_unlock(mutex))
        error_mutex("Mutex unlock err\n", table);
    return(ret);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value, t_philo_args *table)
{
    if(pthread_mutex_lock(mutex))
        error_mutex("Mutex lock err\n", table);
    *dest = value;
    if(pthread_mutex_unlock(mutex))
        error_mutex("Mutex unlock err\n", table);
}

bool sim_finished(t_philo_args *table)
{
    return(get_bool(&table->table_mutex, &table->end_sim, table));
}