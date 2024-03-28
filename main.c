#include "philo.h"

void exit_with_error(char *msg)
{
    write(2, msg, ft_strlen(msg));
    exit(1);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit_with_error("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void destroy_resources(t_simulation *sim) {
    for (size_t i = 0; i < sim->sim_params.philosophers; ++i) {
        pthread_mutex_destroy(&sim->forks[i]);
    }
    free(sim->forks);
    free(sim->philosophers);
}


int main(int argc, char **argv)
{
    t_philo philo_params;
    t_simulation sim;

    if (argc < 5 || argc > 6)
        exit_with_error("Incorrect amount of arguments\n");
    if (!valid_nums(argv + 1))
        exit_with_error("Invalid arguments\n");
    init_philo_params(&philo_params, argv);
    sim.sim_params = philo_params;
    init_forks(&sim);
    init_philos(&sim);
    destroy_resources(&sim);
}