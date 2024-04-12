/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:01:25 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/12 19:39:33 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
    if(pthread_mutex_lock(mutex))
        exit_with_error("Mutex lock error\n");
    *dest = value;
    if(pthread_mutex_unlock(mutex))
        exit_with_error("Mutex unlock error\n");
}

bool get_bool(pthread_mutex_t *mutex, bool *value)
{
    bool    ret;
    if(pthread_mutex_lock(mutex))
        exit_with_error("Mutex lock error\n");
    ret = *value;
    if(pthread_mutex_unlock(mutex))
        exit_with_error("Mutex unlock error\n");
    return(ret);
}

/*LONG*/
long get_long(pthread_mutex_t *mutex, long *value)
{
    long    ret;
    if(pthread_mutex_lock(mutex))
        exit_with_error("Mutex lock error\n");
    ret = *value;
    if(pthread_mutex_unlock(mutex))
        exit_with_error("Mutex unlock error\n");
    return(ret);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
    if(pthread_mutex_lock(mutex))
        exit_with_error("Mutex lock error\n");
    *dest = value;
    if(pthread_mutex_unlock(mutex))
        exit_with_error("Mutex unlock error\n");
}

bool sim_finished(t_philo_args *table)
{
    return(get_bool(&table->table_mutex, &table->end_sim));
}