#include "philo.h"

//    eat(philo);
//    put_forks(philo);
//    sleep_philo(philo);
//    think(philo);

// Any state change of a philosopher must be formatted as follows:
// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died


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
		if (philo->p_data->someone_died)
			break;
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
	

}