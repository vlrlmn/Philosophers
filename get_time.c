/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:01:27 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/10 14:01:28 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    gettime(t_time  time_code, t_philo_args *table)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
        time_err("Time fetch err\n", table);
    if (SECOND == time_code)
        return(tv.tv_sec + (tv.tv_usec / 1e6));
    else if (MILLISECOND == time_code)
        return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (MICROSECOND == time_code)
        return((tv.tv_sec * 1e6) + tv.tv_usec);
    else    
        time_err("Wrong time input\n", table);
    return(-1);
}

void precise_usleep(long usec, t_philo_args *table)
{
    long start;
    long    elapsed;
    long    remain;
    start = gettime(MICROSECOND, table);

    while(gettime(MICROSECOND, table) - start < usec)
    {
        if(sim_finished(table))
            break ;
        elapsed = gettime(MICROSECOND, table) - start;
        remain = usec - elapsed;
        if (remain > 1e3)
            usleep(remain / 2);
        else
        {
            while(gettime(MICROSECOND, table) - start < usec)
                ;
        }
    }
}