
#include "philo.h"

void free_mem(t_data *data)
{
	int i;

	i = 0;
	if (data->philos)
		free(data->philos);  // Only if allocated with malloc/calloc
	if (data->forks)
		free(data->forks);   // Only if allocated with malloc/calloc
}

void cleanup(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&data->print_msg);
	pthread_mutex_destroy(&data->meals_mutex);

	for (int i = 0; i < data->num_of_philo; i++)
	{
		pthread_mutex_destroy(&data->philos[i].time_mutex);
		pthread_mutex_destroy(&data->forks[i]);
	}
	free_mem(data);
}
