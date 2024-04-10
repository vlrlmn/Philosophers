/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:00:59 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/10 14:01:00 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_status(t_status ph_status, t_philo *philo, t_philo_args *table)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND, table) - table->start_sim;
    if (philo->full)
        return ;
    if(pthread_mutex_lock(&philo->table->write_mutex))
        error_mutex("Mutex lock err\n", table);
    else
    {
        if ((TAKE_FIRST_FORK == ph_status || TAKE_SECOND_FORK == ph_status)
            && !sim_finished(philo->table))
            printf("%-6ld %d has taken a fork'\n", elapsed, philo->id);
        else if(EATING == ph_status && !sim_finished(philo->table))
            printf("%-6ld %d is eating\n", elapsed, philo->id);
        else if(SLEEPING == ph_status && !sim_finished(philo->table))
            printf("%-6ld %d is sleeping\n", elapsed, philo->id);
        else if(THINKING == ph_status && !sim_finished(philo->table))
            printf("%-6ld %d is thinking\n", elapsed, philo->id);
        else if(DIED == ph_status)
            printf("%-6ld %d is sleeping\n", elapsed, philo->id);
    }
    if(pthread_mutex_unlock(&philo->table->write_mutex))
        error_mutex("Mutex unlock err\n", table);
}