
#include "philo.h"

int end(t_data *data)
{
	pthread_mutex_lock(&data->finished);
	if (data->one_dead || data->all_eaten)
	{
		pthread_mutex_unlock(&data->finished);
		return 1;
	}
	pthread_mutex_unlock(&data->finished);
	return 0;
}

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

// void *philo_routine(void *arg)
// {
// 	t_philo *philo;
// 	t_data *data;

// 	philo = (t_philo *)arg;
// 	data = philo->data;
// 	while (!end(data))
// 	{
// 		pthread_mutex_lock(&philo->eating);
// 		pthread_mutex_lock(&data->forks[philo->left_fork]);
// 		print_msg("has taken a fork", philo, data);
// 		pthread_mutex_lock(&data->forks[philo->right_fork]);
// 		print_msg("has taken a fork", philo, data);
// 		pthread_mutex_unlock(&philo->eating);
// 		print_msg("is eating", philo, data);
// 		philo->time_from_meal = ft_get_time(data);

// 		printf("time_to_die = %lld\n", data->time_to_die);
// 		printf("time_to_eat = %lld\n", data->time_to_eat);
// 		printf("time_to_sleep = %lld\n", data->time_to_sleep);
// 		printf("time_from_meal = %lld\n", philo->time_from_meal);
// 		ft_usleep(data->time_to_eat, data);
// 		pthread_mutex_unlock(&data->forks[philo->left_fork]);
// 		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		
// 		printf("philo %d time from last meal = %lld\n", philo->id, ft_get_time(data) - philo->time_from_meal);
// 		if(data->time_to_die != -1)
// 		{
// 			while (ft_get_time(data) - philo->time_from_meal < data->time_to_die)
// 			{
// 				if (end(data))
// 					return (NULL);
// 			}
// 			print_msg("died", philo, data);
// 			pthread_mutex_unlock(&data->forks[philo->left_fork]);
// 			pthread_mutex_unlock(&data->forks[philo->right_fork]);
// 			data->one_dead = 1;
// 			return (NULL);
// 		}
// 		philo->meals_eaten++;
// 		if (data->meals_num != -1 && philo->meals_eaten == data->meals_num)
// 			data->all_eaten = 1;
// 		print_msg("is sleeping", philo, data);
// 		ft_usleep(data->time_to_sleep, data);
// 		print_msg("is thinking", philo, data);
// 	}
// 	return (NULL);
// }

// void *philo_routine(void *arg)
// {
//     t_philo *philo;
//     t_data *data;

//     philo = (t_philo *)arg;
//     data = philo->data;

//     while (!end(data))
//     {
//         // Acquire forks (left fork first to avoid deadlock)
//         pthread_mutex_lock(&data->forks[philo->left_fork]);
//         print_msg("has taken a fork", philo, data);
//         pthread_mutex_lock(&data->forks[philo->right_fork]);
//         print_msg("has taken a fork", philo, data);

//         // Start eating
//         pthread_mutex_lock(&philo->eating);
//         philo->time_from_meal = ft_get_time(data); // Update meal time before printing
//         print_msg("is eating", philo, data);
//         ft_usleep(data->time_to_eat, data);
//         pthread_mutex_unlock(&philo->eating);

//         // Release forks
//         pthread_mutex_unlock(&data->forks[philo->left_fork]);
//         pthread_mutex_unlock(&data->forks[philo->right_fork]);

//         // Check if the philosopher has died
//         long long time_since_meal = ft_get_time(data) - philo->time_from_meal;
//         if (data->time_to_die != -1 && time_since_meal >= data->time_to_die)
//         {
//             print_msg("died", philo, data);
//             pthread_mutex_lock(&data->death_mutex); // Protect shared variable
//             data->one_dead = 1;
//             pthread_mutex_unlock(&data->death_mutex);
//             return (NULL);
//         }

//         // Update meals eaten
//         philo->meals_eaten++;
//         if (data->meals_num != -1 && philo->meals_eaten >= data->meals_num)
//         {
//             pthread_mutex_lock(&data->meals_mutex); // Protect shared variable
//             data->all_eaten = 1;
//             pthread_mutex_unlock(&data->meals_mutex);
//         }

//         // Sleep and think
//         print_msg("is sleeping", philo, data);
//         ft_usleep(data->time_to_sleep, data);
//         print_msg("is thinking", philo, data);
//     }
//     return (NULL);
// }

void *philo_routine(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;

	while (!end(data))
	{
		// Acquire forks (left fork first to avoid deadlock)
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_msg("has taken a fork", philo, data);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_msg("has taken a fork", philo, data);

		// Start eating
		pthread_mutex_lock(&philo->eating);
		print_msg("is eating", philo, data);
		ft_usleep(data->time_to_eat, data);
		pthread_mutex_unlock(&philo->eating);
		
		// Release forks
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		
		// Check if the philosopher has died
		long long time_since_meal = ft_get_time(data) - philo->time_from_meal;
		printf("Philo %d: time_since_meal = %lld, time_to_die = %lld  eaten %d\n",
			philo->id, time_since_meal, data->time_to_die, philo->meals_eaten); // Debug print
			if (data->time_to_die != -1 && time_since_meal >= data->time_to_die)
			{
				print_msg("died", philo, data);
				pthread_mutex_lock(&data->death_mutex);
				data->one_dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
		philo->time_from_meal = ft_get_time(data); // Update meal time before printing

		// Update meals eaten
		philo->meals_eaten++;
		if (data->meals_num != -1 && philo->meals_eaten >= data->meals_num)
		{
			pthread_mutex_lock(&data->meals_mutex);
			data->all_eaten = 1;
			pthread_mutex_unlock(&data->meals_mutex);
		}

		// Sleep and think
		print_msg("is sleeping", philo, data);
		ft_usleep(data->time_to_sleep, data);
		print_msg("is thinking", philo, data);
	}
	return (NULL);
}

void *routine(t_data *data)
{
	int i;
	// int left;
	// int right;

	i = 0;
	// while (i < data->num_of_philo)
	// {
	// 	init_philo(data, i);
	// 	i++;
	// }
	if(data->num_of_philo == 1)
	{
		if_one_philo(data);
		return (NULL);
	}
	else
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]);
			printf("philo %d %dcreated\n", i, data->num_of_philo);
			i++;
		}
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_join(data->philos[i].thread, NULL);
			i++;
		}
	}
//	i = 0;
	// while (i < data->num_of_philo)
	// {
	// 	pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < data->num_of_philo)
	// {
	// 	pthread_join(data->philos[i].thread, NULL);
	// 	i++;
	// }
	return (NULL);
}