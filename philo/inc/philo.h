#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

// tratar se nao existir times_a_philo_must_eat;
typedef struct s_data
{
	int				n_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			times_a_philo_must_eat;
	long			time_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex; 
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	long			meals_eaten;
	pthread_mutex_t	meal_mutex;
	t_data			*p_data;
}	t_philo;

#endif