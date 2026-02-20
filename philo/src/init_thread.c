#include "philo.h"

// fazer a função routine

void	*routine(void *arg)
{
	t_philo	*philo;
	int		simulation_on;

	philo = (t_philo *)arg;
	simulation_on = 1;
	while (simulation_on)
	{
		// take_forks()
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
