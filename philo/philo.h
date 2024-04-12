/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:18:32 by vlomakin          #+#    #+#             */
/*   Updated: 2024/04/12 20:05:01 by lomakinaval      ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_philosopher t_philo;

typedef	struct s_fork
{
	pthread_mutex_t				fork;
	int							fork_id;
}		
							t_fork;
typedef struct s_table
{
	int						ph_amount;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						meals;
	unsigned long long		start_sim;
	bool					end_sim;
	t_fork					*forks;
	t_philo					*philos;
	bool					all_threads_ready;
	pthread_mutex_t			table_mutex;
	pthread_mutex_t			write_mutex;
	pthread_t				monitor;
	long					threads_run_num;
}								t_philo_args;

typedef struct s_philosopher
{
	t_philo_args				*table;
	int							id;
	long						last_meal_time;
	int							meals_counter;
	t_fork						*first_fork;
	t_fork						*second_fork;
	pthread_t					thread_id;
	bool						full;
	pthread_mutex_t				philo_mutex;
}									t_philo;



typedef enum et_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time;

typedef enum e_philo_stat
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_status;

void				init_table(t_philo_args *table);
void				init_thread(t_philo_args *table);
bool				valid_nums(char **argv);
int					ft_atol(char *str);
int					ft_strlen(char *str);
void				*philo_routine(void *arg);
int					ft_isdigit(int c);
void				exit_with_error(char *msg);
void				parse_args(t_philo_args *table, char **argv);
bool				sim_finished(t_philo_args *table);
void				set_long(pthread_mutex_t *mutex, long *dest, long value);
long				get_long(pthread_mutex_t *mutex, long *value);
bool				get_bool(pthread_mutex_t *mutex, bool *value);
void				set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void				wait_all_threads(t_philo_args *table);
long				gettime(t_time  time_code);
void				precise_usleep(long usec, t_philo_args *table);
void				write_status(t_status ph_status, t_philo *philo, t_philo_args *table);
void				*monitor_dinner(void *data);
bool				all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void				increase_long(pthread_mutex_t *mutex, long *value);
void				think(t_philo *philo, t_philo_args *table, bool pre_sim);
void				de_synch(t_philo *philo);
void				*one_philo(void *arg);
void				*philo_routine(void *data);
#endif