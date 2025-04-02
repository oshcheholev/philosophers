/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:44:25 by oshcheho          #+#    #+#             */
/*   Updated: 2025/04/02 17:14:11 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *msg, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_msg);
	printf("%lli %d %s\n", ft_get_time(data), philo->id + 1, msg);
	pthread_mutex_unlock(&data->print_msg);
}

void	if_one_philo(t_data *data)
{
	pthread_mutex_lock(&(data->forks[0]));
	print_msg("has taken a fork", &data->philos[0], data);
	ft_usleep(data->time_to_die, data);
	print_msg("died", &data->philos[0], data);
	pthread_mutex_unlock(&(data->forks[0]));
	data->one_dead = 1;
}

int	check_args(int argc, char **argv)
{
	int	arg;

	arg = 1;
	while (arg < argc)
	{
		if (ft_is_num(argv[arg]))
			return (1);
		if (ft_atoi(argv[arg]) == 0)
			return (1);
		if (ft_atoi(argv[arg]) < 0)
			return (1);
		arg++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (check_args(argc, argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	if (data.num_of_philo == 1)
	{
		if_one_philo(&data);
		return (1);
	}
	if (routine(&data))
		return (1);
	return (0);
}
