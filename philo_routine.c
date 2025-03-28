
#include "philo.h"
#include <pthread.h>

// int end(t_data *data)
// {
// 	pthread_mutex_lock(&data->finished);
// 	if (data->one_dead || data->all_eaten)
// 	{
// 		pthread_mutex_unlock(&data->finished);
// 		return 1;
// 	}
// 	pthread_mutex_unlock(&data->finished);
// 	return 0;
// }

void	print_msg(char *msg, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_msg);
	printf("%lli %d %s\n", ft_get_time(data), philo->id + 1, msg);
	pthread_mutex_unlock(&data->print_msg);
}



void	if_one_philo(t_data *data)
{
	printf("num %d\n", data->num_of_philo);
	// if (data->num_of_philo == 1)
	// {
		pthread_mutex_lock(&(data->forks[0]));
//		pthread_mutex_lock(&(data->print_msg));
		print_msg("has taken a fork", &data->philos[0], data);
		ft_usleep(data->time_to_die, data);
		print_msg("died", &data->philos[0], data);
//		pthread_mutex_unlock(&(data->print_msg));
pthread_mutex_unlock(&(data->forks[0]));
data->one_dead = 1;
	// }
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;
	
	while (1)
	{
		
		if(check_if_ok(data))
			break;
		if (philo->id % 2 == 1) 
			ft_usleep(1, data); // Small delay for odd philosophers
		
		// Попытка взять вилки
		if (pthread_mutex_lock(&data->forks[philo->left_fork]) == 0)
		{
			//			printf("philo %d  %d  %d\n", philo->id, data->one_dead, data->all_eaten);
			if(check_if_ok(data))
			{
				pthread_mutex_unlock(&data->forks[philo->left_fork]);
				break;
			}
			print_msg("has taken a fork", philo, data);
			
			if (pthread_mutex_lock(&data->forks[philo->right_fork]) == 0)
			{
				if(check_if_ok(data))
				{
					pthread_mutex_unlock(&data->forks[philo->right_fork]);
					pthread_mutex_unlock(&data->forks[philo->left_fork]);
					break;
				}
				print_msg("has taken a fork", philo, data);
				
				// Начинает есть
				pthread_mutex_lock(&philo->time_mutex);
				philo->time_from_meal = ft_get_time(data);
				philo->meals_eaten++;
				pthread_mutex_unlock(&philo->time_mutex);
				
				pthread_mutex_lock(&philo->eating_mutex);
				philo->is_eating = 1;
				pthread_mutex_unlock(&philo->eating_mutex);
				print_msg("is eating", philo, data);
				ft_usleep(data->time_to_eat, data);
				
				// Освобождает вилки
				pthread_mutex_unlock(&data->forks[philo->right_fork]);
			}
			pthread_mutex_unlock(&data->forks[philo->left_fork]);
		}
		
		// Спит
		if(!check_if_ok(data))
		{
			pthread_mutex_lock(&philo->eating_mutex);
			philo->is_eating = 0;
			pthread_mutex_unlock(&philo->eating_mutex);
			print_msg("is sleeping", philo, data);
			ft_usleep(data->time_to_sleep, data);
		}
		if(!check_if_ok(data))
		{
			print_msg("is thinking", philo, data);
			ft_usleep(1, data);
		}
		// Думает
	}
	return NULL;
}


int routine(t_data *data)
{
	int i;
	i = 0;
	if(data->num_of_philo == 1)
	{
		if_one_philo(data);
		return (1);
	}
	else
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]))
			{
				while (--i >= 0)
				{
					pthread_join(data->philos[i].thread, NULL);
				}
				return (1);
			}
			i++;
		}
		// if (monitor(data))
		// 	return (1);
		if (monitor(data))  // If monitor detects termination
		{
			i = 0;
			while (i < data->num_of_philo)
			{
				pthread_join(data->philos[i].thread, NULL); // Join all threads
				i++;
			}
			cleanup(data);
			return (1);
		}
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_join(data->philos[i].thread, NULL);
			i++;
		}
	}
	return (0);
}
