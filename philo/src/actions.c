#include "philo.h"

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
	while (get_time() - time_start  < philo->p_data->time_to_eat)
	{
		pthread_mutex_lock(&philo->p_data->death_mutex);	
		if (philo->p_data->someone_died)
		{
			pthread_mutex_unlock(&philo->p_data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->p_data->death_mutex);
		usleep(100);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
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
        	break;
    	}
    	pthread_mutex_unlock(&philo->p_data->death_mutex);
		usleep(100);
	}
}

void	think(t_philo *philo)
{
	long	thinking_time;

	print_status(philo, "is thinking");
	usleep(100);
}
