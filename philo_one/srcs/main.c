#include "philo_one.h"

#include <stdio.h> //TODO debug

void		*routine(void *p_data)
{
	(void)p_data;
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
	if (!(env.philos = (t_philo*)malloc(sizeof(t_philo) * env.options.number_of_philosopher)))
		goto end;
	if (init_philos(&env))
	{
		//TODO effacer les process cree, free env philos et quitter
		goto end;
	}
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
