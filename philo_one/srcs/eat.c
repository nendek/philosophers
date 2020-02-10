#include "philo_one.h"

int			take_forks(t_philo *philo)
{
	philo->action = FORKING;

	pthread_mutex_lock(&(philo->env->forks[philo->f_right]));
	pthread_mutex_lock(&(philo->env->forks[philo->f_left]));

	pthread_mutex_lock(&(philo->env->mutex_free_fork));
	pthread_mutex_unlock(&(philo->env->mutex_free_fork));

	return (print_message(philo->env, philo->num, FORKING));
}

int			free_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->mutex_free_fork));

	pthread_mutex_unlock(&(philo->env->forks[philo->f_right]));
	pthread_mutex_unlock(&(philo->env->forks[philo->f_left]));

	if (print_message(philo->env, philo->num, SLEEPING) == 1)
		return (1);

	pthread_mutex_unlock(&(philo->env->mutex_free_fork));
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
		philo->full = 0;
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
