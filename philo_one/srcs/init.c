#include "philo_one.h"

int		init_options(int ac, char **av, t_options *options)
{
	int	i;

	(void)options;
	i = 1;
	while (i < ac)
	{
		if ((ft_all_is_digit(av[i])) == -1)
			return (-1);
		i++;
	}
	options->time_to_die = ft_atol(av[1]);
	options->time_to_eat = ft_atol(av[2]);
	options->time_to_sleep = ft_atol(av[3]);
	options->number_of_time_each_philosophers_must_eat = 0;
	if (ac == 5)
		options->number_of_time_each_philosophers_must_eat = ft_atol(av[4]);
	return (0);
}
