#include "philo_one.h"

void		*routine(void *p_data)
{
	t_philo *philo;

	philo = (t_philo*)p_data;
	while (1)
	{
		if (take_forks(philo) == 1)
		{
			pthread_mutex_unlock(&(philo->env->forks[philo->f_right]));
			pthread_mutex_unlock(&(philo->env->forks[philo->f_left]));
			goto exit_thread;
		}
		if (eat(philo) == 1)
			goto exit_thread;
		if (free_forks(philo) == 1)
			goto free_mutex;
		snooze(philo);
		if (think(philo) == 1)
			goto exit_thread;
	}
free_mutex:
	pthread_mutex_unlock(&(philo->env->mutex_free_fork));
exit_thread:
	pthread_mutex_unlock(&(philo->env->mutex_write));
	return (0);
}

static void	check_all_thread(t_env *env)
{
	int i = 0;

	while (i < env->options.number_of_philosopher)
	{
		pthread_join(env->philos[i].thread, NULL);
		i++;
	}
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
				env->time_end_simulation = get_timestamp_ms();
				print_message(env, i + 1, DEAD);
				check_all_thread(env);
				return(0);
			}
			check |= env->philos[i].full;
		}
		if (!check)
		{
			env->time_end_simulation = get_timestamp_ms();
			env->simulation_end = 1;
			check_all_thread(env);
			return (0);
		}
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
	monitor(&env);
	flush_buf(&env);
	clean_env(&env);
	return (EXIT_SUCCESS);
}
