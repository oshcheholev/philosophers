/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:38:37 by oshcheho          #+#    #+#             */
/*   Updated: 2025/03/31 13:38:37 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->eating_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating_mutex);
	if (!check_if_ok(data))
	{
		print_msg("is sleeping", philo, data);
		ft_usleep(data->time_to_sleep, data);
	}
}

void	do_think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->eating_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating_mutex);
	if (!check_if_ok(data))
	{
		pthread_mutex_lock(&philo->time_mutex);
		if (philo->meals_eaten >= data->meals_num)
		{
			pthread_mutex_unlock(&philo->time_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->time_mutex);
		print_msg("is thinking", philo, data);
	}
}

void	take_forks_and_eat(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&data->forks[philo->left_fork]) == 0)
	{
		if (check_if_ok(data))
			return ((void)pthread_mutex_unlock(&data->forks[philo->left_fork]));
		print_msg("has taken a fork", philo, data);
		if (pthread_mutex_lock(&data->forks[philo->right_fork]) == 0)
		{
			if (check_if_ok(data))
				return ((void)(pthread_mutex_unlock(\
					&data->forks[philo->right_fork]), \
					pthread_mutex_unlock(&data->forks[philo->left_fork])));
			print_msg("has taken a fork", philo, data);
			pthread_mutex_lock(&philo->time_mutex);
			philo->time_from_meal = ft_get_time(data);
			philo->meals_eaten++;
			pthread_mutex_unlock(&philo->time_mutex);
			pthread_mutex_lock(&philo->eating_mutex);
			philo->is_eating = 1;
			pthread_mutex_unlock(&philo->eating_mutex);
			print_msg("is eating", philo, data);
			ft_usleep(data->time_to_eat, data);
			pthread_mutex_unlock(&data->forks[philo->right_fork]);
		}
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		do_think(data, philo);
		if (check_if_ok(data))
			break ;
		if (philo->id % 2 != 1 && data->num_of_philo % 2 == 1)
			ft_usleep(20, data);
		take_forks_and_eat(philo, data);
		do_sleep(data, philo);
	}
	return (NULL);
}

int	routine(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&data->philos[i].thread, \
			NULL, &philo_routine, &data->philos[i]))
		{
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (1);
		}
	}
	if (monitor(data))
	{
		i = -1;
		while (++i < data->num_of_philo)
			pthread_join(data->philos[i].thread, NULL);
		cleanup(data);
		return (1);
	}
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}
