#include "../inc/philo.h"

static void	cleanup(t_data *rules);

int	main(int argc, char **argv)
{
	t_data	rules;

	if (argc != 5 && argc != 6)
		return (0);
	if (!parser_input(&rules, argc, argv))
		return (1);
	if (!init_data(&rules))
		return (1);
	start_simulation(&rules);
	cleanup(&rules);
	return (0);
}

void	cleanup(t_data *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
	free(rules->forks);
	free(rules->philos);
}
