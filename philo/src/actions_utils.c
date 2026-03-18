#include "../inc/philo.h"

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	print_status(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->p_data->death_mutex);
	if (philo->p_data->someone_died && ft_strcmp(action, "died") != 0)
	{
		pthread_mutex_unlock(&philo->p_data->death_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->p_data->print_mutex);
	timestamp = get_time() - philo->p_data->time_start;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->p_data->print_mutex);
	pthread_mutex_unlock(&philo->p_data->death_mutex);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
