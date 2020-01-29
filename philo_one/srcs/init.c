#include "philo_one.h"

static int	init_philos(t_env *env)
{
	for (int i = 0; i < env->options.number_of_philosopher; i++)
	{
		env->philos[i].num = i + 1;
		env->philos[i].action = WAITING;
		env->philos[i].last_eat = 0;
		env->philos[i].last_sleep = 0;
		env->philos[i].last_think = 0;
		env->philos[i].time_of_die = 0;
		int ret = pthread_create(&(env->philos[i].thread), NULL, routine, (void*)&env->philos[i]);
		if (ret)
			return i;
	}
	return (0);
}

int		init_options(int ac, char **av, t_options *options)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if ((ft_all_is_digit(av[i])) == -1)
			return (-1);
		i++;
	}
	options->number_of_philosopher = ft_atol(av[1]);
	if (options->number_of_philosopher > _POSIX_THREAD_THREADS_MAX)
		return (-1);
	options->time_to_die = ft_atol(av[2]);
	options->time_to_eat = ft_atol(av[3]);
	options->time_to_sleep = ft_atol(av[4]);
	options->number_of_time_each_philosophers_must_eat = 0;
	if (ac == 6)
		options->number_of_time_each_philosophers_must_eat = ft_atol(av[5]);
	return (0);
}

int		init_env(t_env *env)
{
	if (!(env->philos = (t_philo*)malloc(sizeof(t_philo) * env->options.number_of_philosopher)))
		goto error;
	if (!(env->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * env->options.number_of_philosopher)))
	{
		free(env->philos);
		goto error;
	}
	if (init_philos(env))
	{
		//TODO effacer les process cree, free env philos et env forks et quitter
		free(env->forks);
		free(env->philos);
		goto error;
	}
	for (int i = 0; i < env->options.number_of_philosopher; i++)
	{
		pthread_mutex_init(&(env->forks[i]), NULL);
	}
	goto end;
error:
	return (-1);
end:
	return (0);
}

