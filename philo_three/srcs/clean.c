#include "philo_three.h"

void		clean_env(t_env *env)
{
	for (int j = 0; j < env->nb_child; j++)
		kill(env->pids[j], SIGKILL);
// 	sem_close(env->forks_sem);
// 	sem_close(env->write_sem);
// 	sem_close(env->check_full_sem);
	free(env->philos);
	free(env->pids);
}
