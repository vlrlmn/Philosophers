/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:01:17 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/10 14:13:12 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo, t_philo_args *table)
{
    long elapsed;
    long t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full, table))
        return(false);
    elapsed = gettime(MILLISECOND, table) - get_long(&philo->philo_mutex, &philo->last_meal_time, table);
    t_to_die = philo->table->time_to_die / 1e3;
    if(elapsed > t_to_die)
        return (true);
    return (false);
}

void *monitor_dinner(void *data)
{
    int i;
    t_philo_args    *table;
    table = (t_philo_args *)data;

    while(!all_threads_running(&table->table_mutex, &table->threads_run_num, table->ph_amount, table))
        ;
    while(!sim_finished(table))
    {
        i = -1;
        while(++i < table->ph_amount && !sim_finished(table))
        {
            if(philo_died(table->philos + i, table))
            {
                set_bool(&table->table_mutex, &table->end_sim, true, table);
                write_status(DIED, table->philos + i, table);
            }
        }
    }
    return(NULL);
}