/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:45:52 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/25 17:45:54 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	else
		return (0);
}

void	exit_free(t_tous *p)
{
	if (p->forks)
		free(p->forks);
	if (p->thr)
		free(p->thr);
	if (p->philo)
		free(p->philo);
}

void	ft_exit_success(t_tous *p)
{
	int	i;

	i = 0;
	if (p->count_ph == 1)
		pthread_mutex_destroy(&p->forks[i]);
	else
	{
		while (i < p->count_ph)
		{
			pthread_mutex_destroy(&p->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&p->death_mutex);
	exit_free(p);
}
