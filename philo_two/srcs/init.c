#include "philo_two.h"

static int	init_philos(t_env *env)
{
	for (int i = 0; i < env->options.number_of_philosopher; i++)
	{
		env->philos[i].num = i + 1;
		env->philos[i].action = FORKING;
		env->philos[i].last_eat = get_timestamp_ms();
		env->philos[i].time_of_die = 0;
		env->philos[i].time_eated = 0;
		env->philos[i].env = env;
		env->philos[i].full = 1;
		int ret = pthread_create(&(env->philos[i].thread), NULL, routine, &(env->philos[i]));
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
	if (options->number_of_philosopher > _POSIX_THREAD_THREADS_MAX || options->number_of_philosopher < 2)
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
	int nb_forks;

	env->buf_index = 0;
	env->simulation_end = 0;
	env->time_end_simulation = 0;
	if (!(env->philos = (t_philo*)malloc(sizeof(t_philo) * env->options.number_of_philosopher)))
		goto error;
	nb_forks = env->options.number_of_philosopher - (env->options.number_of_philosopher % 2);
	if ((env->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT, S_IRWXU, nb_forks)) == SEM_FAILED)
		goto free_philos;
	sem_unlink(FORKS_SEM_NAME);
	if ((env->write_sem = sem_open(WRITE_SEM_NAME, O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		goto free_forks_sem;
	sem_unlink(WRITE_SEM_NAME);
	if (init_philos(env))
		goto free_all;
	goto end;
free_all:
	clean_env(env);
	return (-1);
free_forks_sem:
	sem_close(env->forks_sem);
free_philos:
	free(env->philos);
error:
	return (-1);
end:
	return (0);
}

