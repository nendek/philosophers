#include "philo_one.h"
pthread_t		thread[4];
pthread_mutex_t	mutex[4];	
static int	init_philos(t_env *env)
{
	for (int i = 0; i < env->options.number_of_philosopher; i++)
	{
		env->philos[i].num = i + 1;
		env->philos[i].action = FORKING;
		env->philos[i].last_eat = get_timestamp_ms();
		env->philos[i].last_sleep = 0;
		env->philos[i].time_of_die = 0;
		env->philos[i].time_eated = 0;
		env->philos[i].env = env;
// 		env->philos[i].f_right = (i + 1) % env->options.number_of_philosopher;
// 		env->philos[i].f_left = i;
		env->philos[i].f_left = &(mutex[i]);
		env->philos[i].f_right = &(mutex[(i + 1) % env->options.number_of_philosopher]);
		env->philos[i].full = 1;
// 		memset(env->philos[i], sizeof(
		int ret = pthread_create(&(thread[i]), NULL, routine, &(env->philos[i]));
// 		int ret = pthread_create(&(env->philos[i].thread), NULL, routine, &(env->philos[i]));
		if (ret)
			return i;
// 		pthread_detach(env->philos[i].thread);
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
	env->buf_index = 0;
	env->simulation_end = 0;
	env->time_end_simulation = 0;

	if (!(env->philos = (t_philo*)malloc(sizeof(t_philo) * env->options.number_of_philosopher)))
		goto error;
// 	if (!(env->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * env->options.number_of_philosopher)))
// 		goto free_philos;

	for (int i = 0; i < env->options.number_of_philosopher; i++)
		pthread_mutex_init(&(mutex[i]), NULL);
	pthread_mutex_init(&(env->mutex_write), NULL);
	pthread_mutex_init(&(env->mutex_handle_print), NULL);

	if (init_philos(env))
	{
		//TODO effacer les process cree, free env philos et env forks et quitter
		goto free_forks;
	}
	goto end;

free_forks:
// 	free(env->forks);
// free_philos:
	free(env->philos);
error:
	return (-1);
end:
	return (0);
}

