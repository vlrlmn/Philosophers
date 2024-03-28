#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

typedef struct 
{
    size_t philosophers;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t meals_count;
    bool has_meals_count;
    size_t start_time;
}           t_philo;

typedef struct s_philosopher
{
    int ph_id;                     
    pthread_t thread;        
    size_t last_meal_time;
    size_t meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_simulation *sim;
}               t_philo_each;

typedef struct s_simulation
{
    t_philo         sim_params;
    t_philo_each   *philosophers;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    bool            ph_is_dead;
}               t_simulation;

bool	                valid_nums(char **argv);
int	                    ft_atol(char *str);
int                     ft_strlen(char *str);
void 					init_philo_params(t_philo *philo_params, char **argv);
void    				init_forks(t_simulation *sim);
void                    init_philos(t_simulation *sim);
void 					*philo_routine(void *arg);
int                     ft_isdigit(int c);
void                    exit_with_error(char *msg);
size_t                  get_time(void);
#endif