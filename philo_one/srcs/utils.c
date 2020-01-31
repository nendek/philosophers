#include "philo_one.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int		ft_all_is_digit(char *s)
{
	int i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

long		ft_atol(const char *str)
{
	int	sign;
	long	a;
	int	i;

	a = 0;
	i = 0;
	sign = (str[i] == '-') ? -1 : 1;
	i += (str[i] == '-' || str[i] == '+') ? 1 : 0;
	while (str[i] != '\0')
	{
		a = (a * 10) + (str[i] - '0');
		i++;
	}
	return (sign * a);
}

time_t		get_timestamp_ms(void)
{
	struct timeval tv;

	if ((gettimeofday(&tv, NULL)) == -1)
		return 0;
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void		flush_buf(t_env *env)
{
	write(1, env->buf, env->buf_index);
}

void		print_buf(t_env *env, char c)
{
	env->buf[env->buf_index] = c;
	(env->buf_index)++;
	if (env->buf_index == BUF_SIZE)
	{
		write(1, env->buf, BUF_SIZE);
		env->buf_index = 0;
	}
}

void		print_nbr(t_env *env, long nbr)
{
	if (nbr < 10)
		print_buf(env, nbr + '0');
	else
	{
		print_nbr(env, nbr / 10);
		print_nbr(env, nbr % 10);
	}
}

void		print_str(t_env *env, char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		print_buf(env, str[i]);
		i++;
	}
}

void		end_thread(t_env *env, int philo_num)
{
	pthread_mutex_unlock(&(env->mutex_write));
	env->philos[philo_num - 1].full = 0;
	while (1);
}

void		print_message(t_env *env, int philo, uint8_t action)
{
	pthread_mutex_lock(&(env->mutex_write));
	long timestamp = get_timestamp_ms();
	if (env->simulation_end == 1 && env->time_end_simulation <= timestamp && action != DEAD)
		end_thread(env, philo);
	print_nbr(env, timestamp);
	print_buf(env, ' ');
	print_nbr(env, philo);
	if (action == FORKING)
		print_str(env, " has taken a fork\n");
	else if (action == EATING)
		print_str(env, " is eating\n");
	else if (action == SLEEPING)
		print_str(env, " is sleeping\n");
	else if (action == THINKING)
		print_str(env, " is thinking\n");
	else if (action == DEAD)
		print_str(env, " died\n");
	else
		print_str(env, " has receive a wrong action print\n");
	pthread_mutex_unlock(&(env->mutex_write));
}
