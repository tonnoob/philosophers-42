/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:59:59 by osousa-d          #+#    #+#             */
/*   Updated: 2026/03/22 21:00:00 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <limits.h>

static int	ft_atol_safe(const char *str, long *tmp);
static int	parse_sign(const char *str, int *i);
static int	ft_isdigit(int c);

int	parser_input(t_data *rules, int argc, char **argv)
{
	long	tmp;

	if (!ft_atol_safe(argv[1], &tmp) || tmp <= 0 || tmp > INT_MAX)
		return (0);
	rules->n_philo = (int)tmp;
	if (!ft_atol_safe(argv[2], &tmp) || tmp <= 0)
		return (0);
	rules->time_to_die = tmp;
	if (!ft_atol_safe(argv[3], &tmp) || tmp <= 0)
		return (0);
	rules->time_to_eat = tmp;
	if (!ft_atol_safe(argv[4], &tmp) || tmp <= 0)
		return (0);
	rules->time_to_sleep = tmp;
	rules->times_a_philo_must_eat = -1;
	if (argc == 6)
	{
		if (!ft_atol_safe(argv[5], &tmp) || tmp <= 0)
			return (0);
		rules->times_a_philo_must_eat = tmp;
	}
	return (1);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || (str[*i] == 32))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	ft_atol_safe(const char *str, long *tmp)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = parse_sign(str, &i);
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*tmp = res * sign;
	return (1);
}
