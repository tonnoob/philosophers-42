#include "philo.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_overflow(char *arr)
{
	int		i;
	int		sign;
	long	nbr;
	long	limit;

	nbr = 0;
	sign = 1;
	i = 0;
	if (arr[i] == '-' || arr[i] == '+')
	{
		if (arr[i] == '-')
			sign = -1;
		i++;
	}
	limit = 2147483648;
	if (sign == 1)
		limit = INT_MAX;
	while (ft_isdigit(arr[i]))
	{
		if (nbr > (limit - (arr[i] - '0')) / 10)
			return (0);
		nbr = nbr * 10 + (arr[i] - '0');
		i++;
	}
	return (1);
}