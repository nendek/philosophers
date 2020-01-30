#include "philo_one.h"

void		take_forks(t_philo *philo)
{
	philo->action = FORKING;
	//dprintf(1, "num: %d, avant lock right\n", philo->num);
	//dprintf(1, "num fork right: %d\n",philo->f_right);
	pthread_mutex_lock(&(philo->env->forks[philo->f_right]));
	//dprintf(1, "num: %d, avant lock left\n", philo->num);
	//dprintf(1, "num fork left: %d\n",philo->f_left);
	pthread_mutex_lock(&(philo->env->forks[philo->f_left]));
	//dprintf(1, "num: %d, apres lock left\n", philo->num);
	print_message(philo->env, philo->num, FORKING);
}

void		free_forks(t_philo *philo)
{
	//dprintf(1, "num: %d, avant free right\n", philo->num);
	//dprintf(1, "num fork right: %d\n",philo->f_right);
	pthread_mutex_unlock(&(philo->env->forks[philo->f_right]));
	//dprintf(1, "num: %d, avant free left\n", philo->num);
	//dprintf(1, "num fork left: %d\n", philo->f_left);
	pthread_mutex_unlock(&(philo->env->forks[philo->f_left]));
	print_message(philo->env, philo->num, SLEEPING);
	//dprintf(1, "num: %d, apres free left\n", philo->num);
}

void		eat(t_philo *philo)
{
	philo->action = EATING;
	philo->last_eat = get_timestamp_ms();
	print_message(philo->env, philo->num, EATING);
	usleep(philo->env->options.time_to_eat * 1000);
	philo->time_eated += philo->env->options.time_to_eat;
	if (philo->env->options.number_of_time_each_philosophers_must_eat < philo->time_eated)
		philo->full = 0;
}

void		snooze(t_philo *philo)
{
	philo->action = SLEEPING;
	usleep(philo->env->options.time_to_sleep * 1000);
}

void		think(t_philo *philo)
{
	philo->action = THINKING;
	print_message(philo->env, philo->num, THINKING);
}
