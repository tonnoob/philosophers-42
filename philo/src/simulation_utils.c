/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osousa-d <osousa-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 21:15:48 by osousa-d          #+#    #+#             */
/*   Updated: 2026/03/22 21:23:12 by osousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_thread(t_data *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	return ;
}

int	check_death_status(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->death_mutex);
	stop = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (stop);
}
