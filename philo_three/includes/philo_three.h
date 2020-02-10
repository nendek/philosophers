#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <fcntl.h>

# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

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

# define BUF_SIZE 4096
# define FORKS_SEM_NAME "philo_forks"
# define WRITE_SEM_NAME "philo_mutex_write"
# define CHECK_FULL_SEM_NAME "philo_full"

typedef struct			s_philo
{
	uint16_t		num;
	uint8_t			action;
	time_t			last_eat;
	time_t			time_of_die;
	time_t			time_eated;
	struct s_env		*env;
	int			full;
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
	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*check_full_sem;
	pid_t			*pids;
	char			buf[BUF_SIZE];
	int			    buf_index;
	int             full;
	uint8_t			nb_child;
	pthread_t       thread;

}				t_env;

/*			**** UTILS ****				*/
int			ft_all_is_digit(char *s);
long			ft_atol(const char *s);
time_t			get_timestamp_ms(void);
int			print_message(t_env *env, int philo, uint8_t action);
void			print_nbr(t_env *env, long nbr);
void			print_str(t_env *env, char *str);
void			flush_buf(t_env *env);

/*			**** INIT ****				*/
int			init_options(int ac, char **av, t_options *options);
int			init_env(t_env *env);

/*			**** MAIN ****				*/
void			*routine(t_philo *philo);

/*			**** EAT ****				*/
int			take_forks(t_philo *philo);
int			free_forks(t_philo *philo);
int			eat(t_philo *philo);
void			snooze(t_philo *philo);
int			think(t_philo *philo);

/*			**** CLEAN ****				*/
void			clean_env(t_env *env);

#endif
