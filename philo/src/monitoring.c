#include "philo.h"

int	philo_died(t_philo *philo)
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

int	philos_ate_the_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meals_eaten >= philo->p_data->times_a_philo_must_eat)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	monitoring(t_data *rules)
{
	int	i;
	int	n_philo_satisfied;

	while (1)
	{
		i = 0;
		n_philo_satisfied = 0;
		while (i < rules->n_philo)
		{
			if (philo_died(&rules->philos[i]))
			{
				pthread_mutex_lock(&rules->death_mutex);
				if (rules->someone_died == 0)
				{
					rules->someone_died = 1;
					pthread_mutex_unlock(&rules->death_mutex);
					print_status(&rules->philos[i], "died");
				}
				else
					pthread_mutex_unlock(&rules->death_mutex);
				return;
			}
			if (philos_ate_the_meals(&rules->philos[i]))
				n_philo_satisfied++;
			if (n_philo_satisfied == rules->n_philo)
			{
				pthread_mutex_lock(&rules->death_mutex);
				rules->someone_died = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
