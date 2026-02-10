#include "philo.h"

// number_of_philosophers INT
// time_to_die LONG
// time_to_eat LONG
// time_to_sleep LONG
// [number_of_times_eargch_philosopher_must_eat] - não é obrigatorio o input, mas é mandatorio

// CRIAR STRUCTS
int	valid_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc <= 5 && argc >= 6)
		return (0);
	i = 0;
	while (argv[i][j])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


t_data	parser(int argc, char **argv)
{
	t_data	rules;

	rules.n_philo = atoi(argv[1]);
	rules.time_to_die = atol(argv[2]);
	rules.time_to_eat = atol(argv[3]);
	rules.time_to_sleep = atol(argv[4]);
	if (argc == 6)
		rules.times_a_philo_must_eat = atol(argv[5]);
	if (!check_overflow())

}

int	main(int argc, char **argv)
{
	t_data	rules;

	if (!valid_input(argc, argv))
		return (1);	
	rules = parser(argc, argv)
	if (!data)

	
	return (0);
}
