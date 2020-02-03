#include "philo_two.h"

void		clean_env(t_env *env)
{
	sem_close(env->forks_sem);
	sem_close(env->write_sem);
	free(env->philos);
}
