/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:57:28 by oshcheho          #+#    #+#             */
/*   Updated: 2025/03/31 14:57:28 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_msg);
	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->philos[i].eating_mutex);
		pthread_mutex_destroy(&data->philos[i].time_mutex);
		i++;
	}
	free_mem(data);
}
