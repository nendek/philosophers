#include "philo_one.h"
#include <stdio.h>

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
