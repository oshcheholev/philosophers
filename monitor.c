/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:08:55 by oshcheho          #+#    #+#             */
/*   Updated: 2025/03/27 15:09:27 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"
#include <pthread.h>

int check_all_ate(t_data *data)
{
	int i;
	int res;
	
	i = 0;
	res = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].time_mutex);
		if (data->philos[i].meals_eaten >= data->meals_num)
			res++;
		pthread_mutex_unlock(&data->philos[i].time_mutex);
		i++;
	}
	if (res >= data->num_of_philo)
		return (1);
	return (0);
}

int check_death(t_data *data)
{
	int i;
	long long time;
	
	i = 0;
	while (i < data->num_of_philo)
	{
		time = ft_get_time(data);
		pthread_mutex_lock(&data->philos[i].time_mutex);
//printf("time %lld  philo %d\n", time - data->philos[i].time_from_meal, data->philos[i].id + 1);
		if (time - data->philos[i].time_from_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_msg);
			printf("%lli %d died\n", ft_get_time(data), data->philos[i].id + 1);
			pthread_mutex_lock(&data->philos[i].data->death_mutex);
			data->philos[i].data->one_dead = 1;
			pthread_mutex_unlock(&data->philos[i].data->death_mutex);
			pthread_mutex_unlock(&data->print_msg);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].time_mutex);
		i++;
	}
	return (0);
}

int monitor (t_data *data)
{
	int i;
	
	while (1)
	{
		i = 0;
		// while(i < data->num_of_philo)
		// {
		// 	printf("monitor %lld\n", data->philos[i].time_from_meal);
		// 	i++;
		// }
		// i = 0;
		if (data->meals_num != -1)
		{
			if (check_all_ate(data))
			{
				pthread_mutex_lock(&data->print_msg);
				printf("All philosophers have eaten %d meals\n", data->meals_num);
				pthread_mutex_unlock(&data->print_msg);
				return (1);
			}
		}
		if (check_death(data))
			return (1);
		usleep(1000);
	}
	return (0);
}