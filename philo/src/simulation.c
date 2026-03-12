#include "../inc/philo.h"

static void	*routine(void *arg);
static void create_threads(t_data *rules);
static void	wait_thread(t_data *rules);

void	start_simulation(t_data *rules)
{
	int	i;

	rules->time_start = get_time();
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos[i].last_meal_time = rules->time_start;
		i++;
	}
	create_threads(rules);
	monitoring(rules);
	wait_thread(rules);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->p_data->n_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->p_data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->p_data->someone_died)
	{
		take_forks(philo);
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

static void create_threads(t_data *rules)
{
	int	i;

	rules->time_start = get_time();
	i = 0;
	while (i < rules->n_philo)
	{
		rules->philos[i].last_meal_time = rules->time_start;
		pthread_create(&rules->philos[i].thread, NULL, routine, &rules->philos[i]);
		i++;
	}
	return ;
}

static void	wait_thread(t_data *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	return ;
}