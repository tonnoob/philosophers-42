#include "philo.h"

static int	philo_died(t_philo *philo);
static int	philos_ate_the_meals(t_philo *philo);
static int	set_died(t_philo *philo);
static int	set_philo_satisfied(t_philo *philo, int	*n_philo_satisfied);

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
				set_died(&rules->philos[i]);
				return ;
			}
			if (set_philo_satisfied(&rules->philos[i], &n_philo_satisfied))
				return ;
			i++;
		}
		usleep(100);
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
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meals_eaten == philo->p_data->times_a_philo_must_eat)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
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
	else
		pthread_mutex_unlock(&philo->p_data->death_mutex);
	return (0);
}

static int	set_philo_satisfied(t_philo *philo, int	*n_philo_satisfied)
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
