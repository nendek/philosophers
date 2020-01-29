#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>

# include <sys/time.h>
# include <sys/types.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

typedef struct		s_philo
{
	uint16_t	num;
	uint8_t		action;
	//voir les fourchettes
	suseconds_t	last_fork;
	suseconds_t	last_eat;
	suseconds_t	last_sleep;
	suseconds_t	last_think;
	suseconds_t	time_of_die;
}			t_philo;

typedef struct		s_options
{
	suseconds_t	time_to_die;
	suseconds_t	time_to_eat;
	suseconds_t	time_to_sleep;
	suseconds_t	number_of_time_each_philosophers_must_eat;
}			t_options;

/*			**** UTILS ****				*/
int		ft_all_is_digit(char *s);
long		ft_atol(const char *s);
suseconds_t	get_timestamp_us(void);

/*			**** INIT ****				*/
int		init_options(int ac, char **av, t_options *options);


#endif
