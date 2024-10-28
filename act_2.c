/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:47:55 by zserobia          #+#    #+#             */
/*   Updated: 2024/10/19 15:48:05 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act_1_philo(t_ph *philo)
{
	long	start_time;

	pthread_mutex_lock(&philo->common->print);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->common->start_process, philo->index);
	pthread_mutex_unlock(&philo->common->print);
	start_time = get_time();
	while (1)
	{
		if (get_time() - start_time >= philo->common->time_to_die)
			break ;
	}
	pthread_mutex_lock(&philo->common->print);
	printf("%ld %d died\n", get_time() - philo->common->start_process,
		philo->index);
	pthread_mutex_unlock(&philo->common->print);
}

int	act_2(t_ph *philo)
{
	if (take_forks(philo))
		return (1);
	if (eating(philo))
		return (1);
	if (sleeping(philo))
		return (1);
	if (thinking(philo))
		return (1);
	return (0);
}

void	*act(void *s)
{
	t_ph	*philo;

	philo = (t_ph *)s;
	pthread_mutex_lock(&philo->common->death_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->common->death_mutex);
	if (philo->common->count_ph == 1)
	{
		act_1_philo(philo);
		return (NULL);
	}
	if (philo->index % 2 == 0)
		usleep(philo->common->time_to_eat * 0.2 * 1000);
	while (1)
	{
		if (act_2(philo))
			return (NULL);
	}
	return (NULL);
}
