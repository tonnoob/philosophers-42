/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 21:16:21 by osousa-d          #+#    #+#             */
/*   Updated: 2026/03/22 21:17:53 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	create_threads(t_data *rules);
static void	handle_single_philo(t_philo *philo);
static int	is_full(t_philo *philo);
static void	*routine(void *arg);

void	start_simulation(t_data *rules)
{
	int	i;

	rules->time_start = get_time();
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos[i].last_meal_time = rules->time_start;
		i++;
	}
	create_threads(rules);
	monitoring(rules);
	wait_thread(rules);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->p_data->n_philo == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_death_status(philo->p_data))
	{
		if (is_full(philo))
			break ;
		take_forks(philo);
		eat(philo);
		if (check_death_status(philo->p_data))
			break ;
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

static int	is_full(t_philo *philo)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->p_data->times_a_philo_must_eat != -1
		&& philo->meals_eaten >= philo->p_data->times_a_philo_must_eat)
		full = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	usleep(philo->p_data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

static void	create_threads(t_data *rules)
{
	int	i;

	rules->time_start = get_time();
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos[i].last_meal_time = rules->time_start;
		pthread_create(&rules->philos[i].thread, NULL,
			routine, &rules->philos[i]);
		i++;
	}
	return ;
}
