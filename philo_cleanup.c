
#include "philo.h"

void cleanup(t_data *data)
{
	pthread_mutex_destroy(&data->finished);
	pthread_mutex_destroy(&data->print_msg);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meals_mutex);

	for (int i = 0; i < data->num_of_philo; i++)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
}
