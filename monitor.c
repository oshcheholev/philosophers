/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:08:55 by oshcheho          #+#    #+#             */
/*   Updated: 2025/04/02 17:13:41 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_ok(t_data *data)
{
	pthread_mutex_lock(&data->meals_mutex);
	pthread_mutex_lock(&data->death_mutex);
	pthread_mutex_lock(&data->print_msg);
	if (data->one_dead || data->all_eaten)
	{
		pthread_mutex_unlock(&data->print_msg);
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->print_msg);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->meals_mutex);
	return (0);
}

void	set_init_delay(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	if (philo->id % 2 != 1 && data->num_of_philo % 2 == 1)
	{
		pthread_mutex_unlock(&philo->time_mutex);
		ft_usleep(10, data);
	}
	else if (philo->id % 2 == 1 && data->num_of_philo % 2 == 0
		&& philo->meals_eaten == 0)
	{
		ft_usleep(1, data);
		pthread_mutex_unlock(&philo->time_mutex);
	}
	else
		pthread_mutex_unlock(&philo->time_mutex);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	res;

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
	{
		pthread_mutex_lock(&data->meals_mutex);
		data->all_eaten = 1;
		pthread_mutex_unlock(&data->meals_mutex);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data)
{
	int			i;
	long long	time;

	i = 0;
	while (i < data->num_of_philo)
	{
		time = ft_get_time(data);
		pthread_mutex_lock(&data->philos[i].time_mutex);
		pthread_mutex_lock(&data->philos[i].eating_mutex);
		if (time - data->philos[i].time_from_meal > data->time_to_die
			&& data->philos[i].is_eating == 0)
		{
			pthread_mutex_lock(&data->philos[i].data->death_mutex);
			print_msg("died", &data->philos[i], data);
			data->philos[i].data->one_dead = 1;
			pthread_mutex_unlock(&data->philos[i].data->death_mutex);
			pthread_mutex_unlock(&data->philos[i].eating_mutex);
			pthread_mutex_unlock(&data->philos[i].time_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].eating_mutex);
		pthread_mutex_unlock(&data->philos[i].time_mutex);
		i++;
	}
	return (0);
}

int	monitor(t_data *data)
{
	while (1)
	{
		if (data->meals_num != -1)
		{
			if (check_all_ate(data))
				return (1);
		}
		if (check_death(data))
			return (1);
		usleep(100);
	}
	return (0);
}
