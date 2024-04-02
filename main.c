#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit_with_error("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int argc, char **argv)
{
     t_philo_args   table;

    if (argc < 5 || argc > 6)
        exit_with_error("Incorrect amount of arguments\n");
    if (!valid_nums(argv + 1))
        exit_with_error("Invalid arguments\n");
    init_table_params(&table, argv);
    init_table(&table);
    init_thread(&table);
}