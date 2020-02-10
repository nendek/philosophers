#include "philo_three.h"

static int	init_philos(t_env *env, int i)
{
	env->philos->num = i + 1;
	env->philos->action = FORKING;
	env->philos->last_eat = get_timestamp_ms();
	env->philos->time_of_die = 0;
	env->philos->time_eated = 0;
	env->philos->env = env;
	env->philos->full = 0;
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
	env->full = 0;
	if (!(env->philos = (t_philo*)malloc(sizeof(t_philo) * 1)))
		goto end;
	if (!(env->pids = (pid_t *)malloc(sizeof(pid_t) * env->options.number_of_philosopher)))
		goto free_philos;
	nb_forks = env->options.number_of_philosopher - (env->options.number_of_philosopher % 2);
	if ((env->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, S_IRWXU, nb_forks)) == SEM_FAILED)
		goto free_pids;
	sem_unlink(FORKS_SEM_NAME);
	if ((env->write_sem = sem_open(WRITE_SEM_NAME, O_CREAT | O_EXCL, S_IRWXU, 1)) == SEM_FAILED)
		goto free_forks_sem;
	sem_unlink(WRITE_SEM_NAME);
	if ((env->check_full_sem = sem_open(CHECK_FULL_SEM_NAME, O_CREAT | O_EXCL, S_IRWXU, 0)) == SEM_FAILED)
		goto free_write_sem;
	sem_unlink(CHECK_FULL_SEM_NAME);

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
			env->nb_child = i - 1;
			goto free_all;
		}
	}
	env->nb_child = env->options.number_of_philosopher;
	return (0);
free_all:
	clean_env(env);
	return (-1);
free_write_sem:
	sem_close(env->write_sem);
free_forks_sem:
	sem_close(env->forks_sem);
free_pids:
	free(env->pids);
free_philos:
	free(env->philos);
end:
	return (-1);
}

