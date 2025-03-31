/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:43:46 by oshcheho          #+#    #+#             */
/*   Updated: 2025/03/31 14:43:46 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ch;
	size_t			i;

	i = 0;
	ch = s;
	while (i < n)
	{
		ch[i] = '\0';
		i++;
	}
}

int	ft_is_num(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > 2147483647)
			return (-1);
	}
	return ((int)res);
}
