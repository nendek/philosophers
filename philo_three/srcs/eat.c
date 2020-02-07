#include "philo_three.h"

int			take_forks(t_philo *philo)
{
	philo->action = FORKING;

	sem_wait(philo->env->forks_sem);
	sem_wait(philo->env->forks_sem);

	sem_wait(philo->env->free_fork_sem);
	sem_post(philo->env->free_fork_sem);

	return (print_message(philo->env, philo->num, FORKING));
}

int			free_forks(t_philo *philo)
{
	sem_wait(philo->env->free_fork_sem);

	sem_post(philo->env->forks_sem);
	sem_post(philo->env->forks_sem);
	if (print_message(philo->env, philo->num, SLEEPING) == 1)
		return (1);;

	sem_post(philo->env->free_fork_sem);
	return (0);

}

int			eat(t_philo *philo)
{

	philo->action = EATING;
	philo->last_eat = get_timestamp_ms();
	if (print_message(philo->env, philo->num, EATING) == 1)
		return (1);
	usleep(philo->env->options.time_to_eat * 1000);
	philo->time_eated += philo->env->options.time_to_eat;
	if (philo->env->options.number_of_time_each_philosophers_must_eat < philo->time_eated)
	{
		if (((philo->env->options.number_of_time_each_philosophers_must_eat) != 0) && (philo->full == 0))
		{
			sem_post(philo->env->check_full_sem);
			philo->full = 1;
		}
	}
	return (0);
}

void		snooze(t_philo *philo)
{
	philo->action = SLEEPING;
	usleep(philo->env->options.time_to_sleep * 1000);
}

int			think(t_philo *philo)
{
	philo->action = THINKING;
	return (print_message(philo->env, philo->num, THINKING));
}
