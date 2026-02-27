#include "philo.h"

// fazer a função routine

void	*routine(void *arg)
{
	t_philo	*philo;
	int		simulation_on;

	philo = (t_philo *)arg;
	philo->p_data->someone_died = 1;
	while (!philo->p_data->someone_died)
	{
		take_forks(philo);
		// eat()
		// sleep
		// think
		simulation_on = 0;
	}
}

void	start_simulation(t_data	*rules)
{
	int i;

	rules->time_start = get_time();
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos[i].last_meal_time = rules->time_start;
		pthread_create(&rules->philos[i].thread, NULL, routine, );
		i++;
	}
	return (0);
}
