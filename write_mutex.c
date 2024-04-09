#include "philo.h"

// void write_status_debug(t_status stat, t_philo *philo, long elapsed)
// {
//     if(TAKE_FIRST_FORK == stat && !sim_finished(philo->table))
//         printf("%6ld %d has taken a fork 1\n", elapsed, philo->id);
//     else if(TAKE_SECOND_FORK == stat && !sim_finished(philo->table))
//         printf("%6ld %d has taken a fork 2\n", elapsed, philo->id);
//     else if (EATING == stat && !sim_finished(philo->table))
//         printf("%6ld %d is eating", elapsed, philo->id);
//     else if (SLEEPING == stat && !sim_finished(philo->table))
//         printf("%6ld %d is sleeping", elapsed, philo->id);
//     else if (THINKING == stat && !sim_finished(philo->table), elapsed, philo->id)
//         printf("%6ld %d is thinking", elapsed, philo->id);
//     else if(DIED == stat)
//         printf("%6ld %d died\n", elapsed, philo->id);
// }

void write_status(t_status ph_status, t_philo *philo, t_philo_args *table)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND, table) - table->start_sim;
    if (philo->full)
        return ;
    if(pthread_mutex_lock(&philo->table->write_mutex))
        error_mutex("Mutex lock err\n", table);
    // if(debug)
    //     write_status_debug(ph_status, philo, elapsed);
    else
    {
        if (TAKE_FIRST_FORK == ph_status || TAKE_SECOND_FORK == ph_status
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