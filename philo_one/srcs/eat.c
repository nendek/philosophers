#include "philo_one.h"

void		take_forks(t_philo *philo)
{
	philo->action = FORKING;
	//take fork rit
	pthread_mutex_lock(&(philo->env->forks[(philo->num + 1) % philo->env->options.number_of_philosopher]));
	//take fork left
	pthread_mutex_lock(&(philo->env->forks[philo->num]));
	//print_message(philo->env, philo->num, FORKING)
}

void		free_forks(t_philo *philo)
{
	//free fork rit
	pthread_mutex_unlock(&(philo->env->forks[(philo->num + 1) % philo->env->options.number_of_philosopher]));
	//free fork left
	pthread_mutex_unlock(&(philo->env->forks[philo->num]));
}

void		eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex_eat));
	philo->action = EATING;
	philo->last_eat = get_timestamp_ms();
	//print_message(philo->env, philo->num, EATING)
	usleep(philo->env->options.time_to_eat * 1000);
	philo->nb_eat += 1;
	pthread_mutex_unlock(&(philo->mutex_eat));
}

void		snooze(t_philo *philo)
{
	philo->action = SLEEPING;
	usleep(philo->env->options.time_to_sleep * 1000);
}
