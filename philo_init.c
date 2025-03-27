
#include "philo.h"

void set_philo_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if(i % 2 != 0)
		{
			data->philos[i].left_fork = (i + 1) % data->num_of_philo;
			data->philos[i].right_fork = i;
		}	
		else
		{
			data->philos[i].left_fork = i;
			data->philos[i].right_fork = (i + 1) % data->num_of_philo;
		}
		i++;
	}
}

void init_philo(t_data *data, int i)
{
		data->philos[i].id = i;
		data->philos[i].is_eating = 0;
		data->philos[i].meals_eaten = 0;
//		data->philos[i].meals_eaten = 0;
		data->philos[i].time_from_meal = ft_get_time(data);
//		data->philos[i].start = ft_get_time(data);
//		pthread_mutex_init(&data->philos[i].eating, NULL);
//		pthread_mutex_init(&data->philos[i].print_msg, NULL);
		pthread_mutex_init(&data->philos[i].time_mutex, NULL);
		data->philos[i].data = data;
	}
	
	int init_data(t_data *data, int argc, char **argv)
	{
		int i;
		
		i = 0;
		data->start = 0;
		data->start = ft_get_time(data);
		data->one_dead = 0;
		data->all_eaten = 0;
		data->num_of_philo = ft_atoi(argv[1]);
		if (argc == 6)
		data->meals_num = ft_atoi(argv[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->philos = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->forks || !data->philos)
		return 1;
	set_philo_forks(data);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 5)
		data->meals_num = -1;
	else
		data->meals_num = ft_atoi(argv[5]);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_msg, NULL);
	pthread_mutex_init(&data->meals_mutex, NULL);
	while (i < data->num_of_philo)
	{
		init_philo(data, i);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

