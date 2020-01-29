#include "philo_one.h"

#include <stdio.h> //TODO debug

void		*routine(void *p_data)
{
	t_philo *philo;

	philo = (t_philo*)p_data;
	philo->last_eat = get_timestamp_ms();
	dprintf(1, "ici %d\n", philo->num);
	dprintf(1, "dans un thread\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_env		env;

	if (argc < 5 || argc > 6)
		goto usage;
	if ((init_options(argc, argv, &(env.options))) == -1)
		goto usage;
	if ((init_env(&env)) == -1)
		return (EXIT_FAILURE);
	for (int i = 0; i < env.options.number_of_philosopher; i++)
	{
		pthread_join(env.philos[i].thread, NULL);
	}
	goto end;
usage:
	write(1, "Usage: ./philo_one number_of_philosopher time_to_die time_to_eat time_to_sleep  [number_of_time_each_philosophers_must_eat]\n", 124);

end:
	return (EXIT_SUCCESS);
}
