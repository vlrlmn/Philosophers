/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:01:27 by lomakinaval       #+#    #+#             */
/*   Updated: 2024/04/12 19:31:33 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    gettime(t_time  time_code)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
        exit_with_error("Time fetch err\n");
    if (SECOND == time_code)
        return(tv.tv_sec + (tv.tv_usec / 1e6));
    else if (MILLISECOND == time_code)
        return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (MICROSECOND == time_code)
        return((tv.tv_sec * 1e6) + tv.tv_usec);
    else    
        exit_with_error("Time fetch err\n");
    return(-1);
}

void precise_usleep(long usec, t_philo_args *table)
{
    long start;
    long    elapsed;
    long    remain;
    start = gettime(MICROSECOND);

    while(gettime(MICROSECOND) - start < usec)
    {
        if(sim_finished(table))
            break ;
        elapsed = gettime(MICROSECOND) - start;
        remain = usec - elapsed;
        if (remain > 1e3)
            usleep(remain / 2);
        else
        {
            while(gettime(MICROSECOND) - start < usec)
                ;
        }
    }
}