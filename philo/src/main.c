#include "philo.h"

// number_of_philosophers INT
// time_to_die LONG
// time_to_eat LONG
// time_to_sleep LONG
// [number_of_times_eargch_philosopher_must_eat] - não é obrigatorio o input, mas é mandatorio

// criar o monitor de morte (tempo de agora - ultima ref > time_to_die)

int	init_data(t_data *rules)
{
// Alocar array de filósofos
// Alocar array de mutex (forks)
// Inicializar mutex
// Inicializar variáveis globais (start_time, stop flag e outras)
}

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
