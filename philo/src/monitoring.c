/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:59:23 by osousa-d          #+#    #+#             */
/*   Updated: 2026/03/22 21:19:30 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philo_died(t_philo *philo);
static int	philos_ate_the_meals(t_philo *philo);
static int	set_died(t_philo *philo);
static int	set_philo_satisfied(t_philo *philo, int *n_philo_satisfied);

void	monitoring(t_data *rules)
{
	int	i;
	int	n_philo_satisfied;

	while (1)
	{
		n_philo_satisfied = 0;
		i = 0;
		while (i < rules->n_philo)
		{
			if (philo_died(&rules->philos[i]))
			{
				set_died(&rules->philos[i]);
				return ;
			}
			if (rules->times_a_philo_must_eat != -1)
			{
				if (set_philo_satisfied(&rules->philos[i], &n_philo_satisfied))
					return ;
			}
			i++;
		}
		usleep(1000);
	}
}

static int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_time() - philo->last_meal_time >= philo->p_data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static int	philos_ate_the_meals(t_philo *philo)
{
	int	ate_enough;

	ate_enough = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meals_eaten >= philo->p_data->times_a_philo_must_eat)
		ate_enough = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (ate_enough);
}

static int	set_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data->death_mutex);
	if (philo->p_data->someone_died == 0)
	{
		philo->p_data->someone_died = 1;
		pthread_mutex_unlock(&philo->p_data->death_mutex);
		print_status(philo, "died");
		return (1);
	}
	pthread_mutex_unlock(&philo->p_data->death_mutex);
	return (1);
}

static int	set_philo_satisfied(t_philo *philo, int *n_philo_satisfied)
{
	if (philos_ate_the_meals(philo))
		(*n_philo_satisfied)++;
	if (*n_philo_satisfied == philo->p_data->n_philo)
	{
		pthread_mutex_lock(&philo->p_data->death_mutex);
		philo->p_data->someone_died = 1;
		pthread_mutex_unlock(&philo->p_data->death_mutex);
		return (1);
	}
	return (0);
}
