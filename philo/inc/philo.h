#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

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
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				someone_died;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	long			meals_eaten;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*p_data;
}	t_philo;

int		parser_input(t_data *rules, int argc, char **argv);
int		init_data(t_data *rules);
long	get_time(void);
void	print_status(t_philo *philo, char *action);
int		ft_strcmp(const char *s1, const char *s2);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);
void	monitoring(t_data *rules);
void	start_simulation(t_data *rules);

#endif