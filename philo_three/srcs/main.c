#include "philo_three.h"

void		*routine(t_philo *philo)
{
	while (1)
	{
		if (take_forks(philo) == 1)
			goto exit_thread;
		if (eat(philo) == 1)
			goto exit_thread;
		if (free_forks(philo) == 1)
			goto free_mutex;
		snooze(philo);
		if (think(philo) == 1)
			goto exit_thread;
	}
free_mutex:
	(void)philo;
// 	pthread_mutex_unlock(&(philo->env->mutex_free_fork));
exit_thread:
// 	pthread_mutex_unlock(&(philo->env->mutex_write));
	exit(-1);
}

static int	monitor(t_env *env)
{
	int		status;
	int		i;
	long	timestamp;

	while(1)
	{
		i = 0;
		while (i < env->options.number_of_philosopher)
		{
			waitpid(env->pids[i], &status, WNOHANG);
			if (WIFEXITED(status) == 1)
			{
				timestamp = get_timestamp_ms();
				goto kill_all;
			}
			i++;
		}
	}
kill_all:
	for (int j = 0; j < env->options.number_of_philosopher; j++)
	{
		kill(env->pids[j], SIGKILL);
	}
	sem_unlink(FORKS_SEM_NAME);
	sem_unlink(WRITE_SEM_NAME);
	sem_unlink(FREE_FORK_SEM_NAME);
	flush_buf(env);
	print_nbr(env, timestamp);
	print_str(env, " ");
	print_nbr(env, i + 1);
	print_str(env, " died\n");
	flush_buf(env);
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
