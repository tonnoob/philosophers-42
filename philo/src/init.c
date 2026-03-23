/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:55:08 by osousa-d          #+#    #+#             */
/*   Updated: 2026/03/22 21:20:45 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	destroy_arr_mutex(pthread_mutex_t *mutex, int size);
static int	init_forks(t_data *rules);
static int	init_global_mutexes(t_data *rules);
static int	init_philos(t_data *rules);

int	init_data(t_data *rules)
{
	rules->someone_died = 0;
	if (!init_forks(rules))
		return (0);
	if (!init_global_mutexes(rules))
	{
		destroy_arr_mutex(rules->forks, rules->n_philo);
		free(rules->forks);
		return (0);
	}
	if (!init_philos(rules))
	{
		destroy_arr_mutex(rules->forks, rules->n_philo);
		free(rules->forks);
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->death_mutex);
		free(rules->philos);
		return (0);
	}
	return (1);
}

static void	destroy_arr_mutex(pthread_mutex_t *mutex, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	return ;
}

static int	init_forks(t_data *rules)
{
	int	i;

	rules->forks = malloc(rules->n_philo * sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (0);
	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			destroy_arr_mutex(rules->forks, i);
			free(rules->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_global_mutexes(t_data *rules)
{
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->print_mutex);
		return (0);
	}
	return (1);
}

static int	init_philos(t_data *rules)
{
	int	i;

	rules->philos = malloc(rules->n_philo * sizeof(t_philo));
	if (!rules->philos)
		return (0);
	i = 0;
	rules->time_start = get_time();
	while (i < rules->n_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->n_philo];
		rules->philos[i].p_data = rules;
		rules->philos[i].philo_is_full = 0;
		i++;
	}
	return (1);
}
