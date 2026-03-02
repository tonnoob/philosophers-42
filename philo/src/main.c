#include "philo.h"

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
