#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo_each *philo = (t_philo_each*)arg;

    while(!philo->sim->ph_is_dead)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("Philosopher %d has taken a left fork\n", philo->ph_id + 1);
        pthread_mutex_lock(philo->right_fork);
        printf("Philosopher %d has taken a rigth fork\n", philo->ph_id + 1);
        philo->last_meal_time = get_time();
        printf("Philosopher %d is eating\n", philo->ph_id + 1);
        usleep(philo->sim->sim_params.time_to_eat * 1000);
        philo->meals_eaten++;
        if (philo->sim->sim_params.has_meals_count && philo->meals_eaten >= philo->sim->sim_params.meals_count)
            break ;
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        printf("Philosopher %d is sleeping\n", philo->ph_id + 1);
        usleep(philo->sim->sim_params.time_to_sleep * 1000);
        printf("Philosopher %d is thinking\n", philo->ph_id + 1);
    }
    return NULL;
}
