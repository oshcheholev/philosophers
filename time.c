/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:58:08 by oshcheho          #+#    #+#             */
/*   Updated: 2025/03/31 14:58:08 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((((long long)time.tv_sec * 1000) + \
	((long long)time.tv_usec / 1000)) - (long long)data->start);
}

long long	ft_usleep(long long milliseconds, t_data *data)
{
	int	start;

	start = ft_get_time(data);
	while (ft_get_time(data) - start < milliseconds)
		usleep(100);
	return (0);
}
