#include "philo.h"

//     take_forks(philo); implementar
//			Ímpares pegam esquerda depois direita
//			Pares pegam direita depois esquerda
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

long	get_time(void)
{
	struct timeval	time;
	long			ms;
	
	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	take_forks(t_philo *philo)
{
	long	timestamp;
	
	timestamp = get_time() - philo->p_data->time_start;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "is eating");
	}
	if (philo->id % 2 != 0)
	
	
}
void	print_status(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->p_data->print_mutex);
	pthread_mutex_lock(&philo->p_data->death_mutex);
	timestamp = get_time() - philo->p_data->time_start;;
	if (philo->p_data->someone_died == 0)
		printf("%ld %d %s\n", timestamp, philo->id, action);
	else
		printf(printf("%ld %d died\n", timestamp, philo->id));
	pthread_mutex_unlock(&philo->p_data->print_mutex);
	pthread_mutex_unlock(&philo->p_data->death_mutex);
}
