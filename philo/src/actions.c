/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:52:07 by osousa-d          #+#    #+#             */
/*   Updated: 2026/03/22 20:54:10 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	long	time_start;

	time_start = get_time();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = time_start;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	while (get_time() - time_start < philo->p_data->time_to_eat)
	{
		if (check_death_status(philo->p_data))
			break ;
		usleep(500);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	if (philo->p_data->times_a_philo_must_eat != -1
		&& philo->meals_eaten >= philo->p_data->times_a_philo_must_eat)
		philo->philo_is_full = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	long	time_start;

	time_start = get_time();
	print_status(philo, "is sleeping");
	while (get_time() - time_start < philo->p_data->time_to_sleep)
	{
		pthread_mutex_lock(&philo->p_data->death_mutex);
		if (philo->p_data->someone_died)
		{
			pthread_mutex_unlock(&philo->p_data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->p_data->death_mutex);
		usleep(100);
	}
}

void	think(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->meal_mutex);
	time_to_think = (philo->p_data->time_to_die
			- (get_time() - philo->last_meal_time)
			- philo->p_data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 500)
		time_to_think = 200;
	print_status(philo, "is thinking");
	usleep(time_to_think * 1000);
}
