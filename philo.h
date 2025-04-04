/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:15:16 by oshcheho          #+#    #+#             */
/*   Updated: 2025/03/31 15:15:16 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		time_from_meal;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	eating_mutex;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				one_dead;
	int				all_eaten;
	int				num_of_philo;
	int				meals_num;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	long long		start;
	pthread_mutex_t	print_msg;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	t_philo			*philos;
}				t_data;

int			routine(t_data *data);
int			monitor(t_data *data);
int			check_if_ok(t_data *data);
int			ft_atoi(char *str);
int			ft_is_num(char *c);
int			init_data(t_data *data, int argc, char **argv);
void		cleanup(t_data *data);
void		print_msg(char *msg, t_philo *philo, t_data *data);
long long	ft_usleep(long long milliseconds, t_data *data);
long long	ft_get_time(t_data *data);

#endif
