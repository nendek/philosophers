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
			goto free_sem;
		snooze(philo);
		if (think(philo) == 1)
			goto exit_thread;
	}
free_sem:
	sem_post(philo->env->forks_sem);
exit_thread:
	sem_post(philo->env->write_sem);
	exit(-1);
}

void	*check_full(void *data)
{
	t_env	*env;
	int		count;

	env = (t_env *)data;
	count = 0;
	while (count < env->options.number_of_philosopher)
	{
		sem_wait(env->check_full_sem);
		count++;
	}
	env->full = 1;
	return (0);
}

static int	monitor(t_env *env)
{
	int     i;
	int     status;
	time_t  timestamp;
	int		print = 0;

	pthread_create(&(env->thread), NULL, check_full, env);
	while(1)
	{
		i = 0;
		while (i < env->options.number_of_philosopher)
		{
			waitpid(env->pids[i], &status, WNOHANG);
			if (WIFEXITED(status) == 1)
				goto kill_all;
			i++;
			if (env->full == 1)
			{
				print = 1;
				goto kill_all;
			}
		}
	}

kill_all:
	timestamp = get_timestamp_ms();
	if (print == 0)
	{
		print_nbr(env, timestamp);
		print_str(env, " ");
		print_nbr(env, i + 1);
		print_str(env, " died\n");
		flush_buf(env);
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
