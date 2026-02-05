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
		if (!check_overflow(argv[i]))
			return (0);
		i++;
	}
			
	//chamar atol em loop
	if ()
}


int	main(int argc, char **argv)
{
	if (!valid_input(argc, argv))
		return (1);
	
	
	return (0);
}
