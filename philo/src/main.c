#include "philo.h"

// number_of_philosophers INT
// time_to_die LONG
// time_to_eat LONG
// time_to_sleep LONG
// [number_of_times_eargch_philosopher_must_eat] - não é obrigatorio o input, mas é mandatorio

// criar o monitor de morte (tempo de agora - ultima ref > time_to_die)

int	init_philos(t_data *rules)
{
	int	i;
	
	rules->philos = malloc(rules->n_philo * sizeof(t_philo));
	if (!rules->philos)
		return (0);
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos->id = i;
		rules->philos->thread = &rules->philos[i];
		rules->philos->last_meal_time = 0;
		rules->philos->meals_eaten = 0;
		rules->philos->left_fork = &rules->forks[i];
		rules->philos->right_fork = &rules->forks[(i + 1) % rules->n_philo];
		rules->philos[i].p_data = rules;
		i++;
	}
	return (1);
}

// Alocar array de mutex (forks) init_forks
// fazer a função all init_data chamando as adjacentes
// Inicializar mutex
// Inicializar variáveis globais (start_time, stop flag e outras)

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

	return (0);
}
