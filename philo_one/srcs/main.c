#include "philo_one.h"

#include <stdio.h> //TODO debug

int		main(int argc, char **argv)
{
	t_options	options;

	if (argc < 5 || argc > 6)
		goto usage;
	if ((init_options(argc, argv, &options)) == -1)
		goto usage;


	goto end;
usage:
	write(1, "Usage: ./philo_one number_of_philosopher time_to_die time_to_eat time_to_sleep  [number_of_time_each_philosophers_must_eat]\n", 124);

end:
	return (0);
}
