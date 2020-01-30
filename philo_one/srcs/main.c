#include "philo_one.h"

#include <stdio.h> //TODO debug

void		*routine(void *p_data)
{
	t_philo *philo;

	philo = (t_philo*)p_data;
	//faire un thread qui check la mort
	while (1)
	{
		take_forks(philo);
		eat(philo);
		free_forks(philo);
		snooze(philo);
		think(philo);
	}
	return (0);
}

static int	monitor(t_env *env)
{
	time_t		now;
	uint8_t		check;
	int		verif_time_eated;

	if (env->options.number_of_time_each_philosophers_must_eat == 0)
		verif_time_eated = 1;
	else
		verif_time_eated = 0;
	while(1)
	{
		check = verif_time_eated;
		now = get_timestamp_ms();
		for (int i = 0; i < env->options.number_of_philosopher; i++)
		{
			if ((now - env->philos[i].last_eat) > env->options.time_to_die)
			{
				print_message(env, i + 1, DEAD);
				return(0);
			}
			check |= env->philos[i].full;
		}
		if (!check)
			return (0);
	}
	return (0);
}

int		exit_usage(void)
{
	write(1, "Usage: ./philo_one number_of_philosopher time_to_die time_to_eat time_to_sleep  [number_of_time_each_philosophers_must_eat]\n", 124);
	return (EXIT_FAILURE);
}

int		main(int argc, char **argv)
{
	t_env		env;

	if (argc < 5 || argc > 6)
		return (exit_usage());
	if ((init_options(argc, argv, &(env.options))) == -1)
		return (exit_usage());
	if ((init_env(&env)) == -1)
		return (EXIT_FAILURE);
	//for (int i = 0; i < env.options.number_of_philosopher; i++)
	//{
	//	pthread_join(env.philos[i].thread, NULL);
	//}
	//faire un thread qui check si il y a des morts ou l'option number of time must eat
	//pthread_join(env.monitor, NULL);
	monitor(&env);
	flush_buf(&env);
	return (EXIT_SUCCESS);
}
