#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>

# include <sys/time.h>
# include <sys/types.h>

# include <bits/local_lim.h>

# define WAITING 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

typedef struct			s_philo
{
	uint16_t		num;
	uint8_t			action;
	pthread_t		thread;
	time_t			last_eat;
	time_t			last_sleep;
	time_t			last_think;
	time_t			time_of_die;
}				t_philo;

typedef struct			s_options
{
	uint16_t		number_of_philosopher;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			number_of_time_each_philosophers_must_eat;
}				t_options;

typedef struct			s_env
{
	t_options		options;
	t_philo			*philos;
	pthread_mutex_t		*forks;
}				t_env;

/*			**** UTILS ****				*/
int		ft_all_is_digit(char *s);
long		ft_atol(const char *s);
time_t		get_timestamp_ms(void);

/*			**** INIT ****				*/
int		init_options(int ac, char **av, t_options *options);
int		init_env(t_env *env);

void		*routine(void *p_data);

#endif
