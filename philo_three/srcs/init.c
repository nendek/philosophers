#include "philo_three.h"

static int	init_philos(t_env *env, int i)
{
	env->philos->num = i + 1;
	env->philos->action = FORKING;
	env->philos->last_eat = get_timestamp_ms();
	env->philos->time_of_die = 0;
	env->philos->time_eated = 0;
	env->philos->env = env;
	env->philos->full = 1;
// 		int ret = pthread_create(&(env->philos[i].thread), NULL, routine, &(env->philos[i]));
// 		if (ret)
// 			return i;
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
	if (options->number_of_philosopher < 2)
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

// 	TODO : gestion d'erreures
	if ((env->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, S_IRWXU, env->options.number_of_philosopher)) == SEM_FAILED)
		goto error;
	if ((env->write_sem = sem_open(WRITE_SEM_NAME, O_CREAT | O_EXCL, S_IRWXU, 1)) == SEM_FAILED)
		goto error;
	if ((env->free_fork_sem = sem_open(FREE_FORK_SEM_NAME, O_CREAT | O_EXCL, S_IRWXU, 1)) == SEM_FAILED)
		goto error;
	if (!(env->philos = (t_philo*)malloc(sizeof(t_philo) * 1)))
		goto error;
	if (!(env->pids = (pid_t *)malloc(sizeof(pid_t) * env->options.number_of_philosopher)))
		goto free_philos;
	for (int i = 0; i < env->options.number_of_philosopher; i++)
	{
		env->pids[i] = fork();
		if (env->pids[i] == 0)
		{
			init_philos(env, i);
			routine(env->philos);
		}
		else if (env->pids[i] < 0)
		{
			// TODO : kill all
			goto free_pids;
		}

	}
// 	if (!(env->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * env->options.number_of_philosopher)))
// 		goto free_philos;

// 	for (int i = 0; i < env->options.number_of_philosopher; i++)
// 		pthread_mutex_init(&(env->forks[i]), NULL);
// 	pthread_mutex_init(&(env->mutex_write), NULL);
// 	pthread_mutex_init(&(env->mutex_free_fork), NULL);

// 	if (init_philos(env))
// 		goto free_pids;
	return (0);

free_pids:
	free(env->pids);
free_philos:
	free(env->philos);
error:
	perror("test: ");
	return (-1);
}

