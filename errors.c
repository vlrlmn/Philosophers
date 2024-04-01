#include "philo.h"

void exit_with_error(char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(1);
}

void free_forks(pthread_mutex_t **forks)
{
    int i;

    i = 0;
    while(forks[i] != NULL)
    {
        pthread_mutex_destroy(forks[i]);
        i++;
    }
    *forks = NULL;
}

void free_forks_and_exit(pthread_mutex_t **forks, char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(1);
}
