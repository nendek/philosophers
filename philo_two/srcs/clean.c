#include "philo_one.h"

void		clean_env(t_env *env)
{
	//int i = 0;
	//while (i < env->options.number_of_philosopher)
	//{
 	//	pthread_mutex_destroy(&(env->forks[i]));
	//	i++;
	//}
	//pthread_mutex_destroy(&(env->mutex_write));
	//pthread_mutex_destroy(&(env->mutex_free_fork));
	//free(env->forks);
	sem_close(env->sem_forks);
	sem_close(env->sem_mutex_write);
	free(env->philos);
}
