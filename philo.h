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

typedef struct s_philosopher
{
    int                 ph_id;              
    pthread_t           thread;        
    size_t              last_meal_time; //last_meal
    size_t              meals_eaten; //num_meals
    pthread_mutex_t     *left_fork;
    pthread_mutex_t     *right_fork;
    int                 flag;
    int                 meals_done; //philo_is_full
}               t_philo;

typedef struct 
{
    size_t              ph_amount; //num_of_philo
    size_t              time_to_die;
    size_t              time_to_eat;
    size_t              time_to_sleep;
    size_t              meals_count;
    int                 id; //index
    size_t              start_time; //start
    t_philo             *philos;
    pthread_mutex_t     **forks;
    pthread_mutex_t     *sim; //typing
    struct timeval      timer; //timer
}           t_philo_args;


// typedef struct s_simulation
// {
//     t_philo         sim_params;
//     t_philo_each   *philosophers;
//     pthread_mutex_t *forks;
//     pthread_mutex_t write_mutex;
//     bool            ph_is_dead;
// }               t_simulation;

void init_table_params(t_philo_args *table, char **argv);
void init_table(t_philo_args *table);
void init_thread(t_philo_args   *table);
bool	                valid_nums(char **argv);
int	                    ft_atol(char *str);
int                     ft_strlen(char *str);
void 					*philo_routine(void *arg);
int                     ft_isdigit(int c);
void                    exit_with_error(char *msg);
size_t                  get_time(void);

/*Errors and free mem*/
void exit_with_error(char *msg);
void free_forks_and_exit(pthread_mutex_t **forks, char *msg);
void init_thread(t_philo_args   *table);
void init_table(t_philo_args *table);
void init_table_params(t_philo_args *table, char **argv);

#endif