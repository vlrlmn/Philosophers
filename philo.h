/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:32 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/04 14:40:30 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				ph_id;
	pthread_t		thread;
	long long last_meal_time; //last_meal
	int meals_eaten;          //num_meals
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				flag;
	int meals_done; //philo_is_full
}					t_philo;

typedef struct
{
	int ph_amount; //num_of_philo
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_count;
	int id;                        //index
	unsigned long long start_time; //start
	t_philo			*philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t *sim; //typing
	struct timeval timer; //timer
}					t_philo_args;

// typedef struct s_simulation
// {
//     t_philo         sim_params;
//     t_philo_each   *philosophers;
//     pthread_mutex_t *forks;
//     pthread_mutex_t write_mutex;
//     bool            ph_is_dead;
// }               t_simulation;

void				init_table_params(t_philo_args *table, char **argv);
void				init_table(t_philo_args *table);
void				init_thread(t_philo_args *table);
bool				valid_nums(char **argv);
int					ft_atol(char *str);
int					ft_strlen(char *str);
void				*philo_routine(void *arg);
int					ft_isdigit(int c);
void				exit_with_error(char *msg);
int					get_time(void);

/*Errors and free mem*/
void				exit_with_error(char *msg);
void				free_forks_and_exit(pthread_mutex_t **forks, char *msg);
void				init_table_params(t_philo_args *table, char **argv);
void				change_status(t_philo_args *table, char *str, int i,
						int flag);
void				free_forks(pthread_mutex_t **forks);
void				pthread_failed(char *msg);
#endif