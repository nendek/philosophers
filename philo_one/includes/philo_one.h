#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>

#include <stdio.h>

# include <sys/time.h>
# include <sys/types.h>

# ifdef __linux__
#  include <bits/local_lim.h>
# endif

# ifdef __APPLE__
#  include <limits.h>
# endif

# define FORKING 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define WAITING 5

# define BUF_SIZE 4096

typedef struct			s_philo
{
	uint16_t		num;
	uint8_t			action;
	pthread_t		thread;
	time_t			last_eat;
	time_t			last_sleep;
	time_t			time_of_die;
	time_t			time_eated;
	struct s_env		*env;
	int			full;
// 	int			f_left;
// 	int			f_right;
	pthread_mutex_t		*f_left;
	pthread_mutex_t		*f_right;
}				t_philo;

typedef struct			s_options
{
	uint16_t			number_of_philosopher;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	time_t				number_of_time_each_philosophers_must_eat;
}						t_options;

typedef struct			s_env
{
	t_options			options;
	t_philo				*philos;
// 	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_write;
	pthread_mutex_t		mutex_handle_print;
	pthread_t		monitor;
	char				buf[BUF_SIZE];
	int					buf_index;

	int					simulation_end;
	time_t				time_end_simulation;
}						t_env;

/*			**** UTILS ****				*/
int			ft_all_is_digit(char *s);
long		ft_atol(const char *s);
time_t		get_timestamp_ms(void);
void		print_message(t_env *env, int philo, uint8_t action);
void		flush_buf(t_env *env);

/*			**** INIT ****				*/
int			init_options(int ac, char **av, t_options *options);
int			init_env(t_env *env);

/*			**** MAIN ****				*/
void		*routine(void *p_data);

/*			**** EAT ****				*/
void		take_forks(t_philo *philo);
void		free_forks(t_philo *philo);
void		eat(t_philo *philo);
void		snooze(t_philo *philo);
void		think(t_philo *philo);


#endif
