/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:44:19 by zserobia          #+#    #+#             */
/*   Updated: 2024/10/02 19:44:27 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_ph *philo)
{
	long	current_time;
	long	time_since_last_eat;

	pthread_mutex_lock(&philo->common->death_mutex);
	if (philo->common->stop || philo->common->dead)
	{
		pthread_mutex_unlock(&philo->common->death_mutex);
		return (1);
	}
	current_time = get_time();
	time_since_last_eat = current_time - philo->last_eat;
	if (time_since_last_eat >= philo->common->time_to_die)
	{
		philo->common->dead = 1;
		philo->common->stop = 1;
		pthread_mutex_unlock(&philo->common->death_mutex);
		pthread_mutex_lock(&philo->common->print);
		printf("%ld %d died\n", current_time - philo->common->start_process,
			philo->index);
		pthread_mutex_unlock(&philo->common->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->common->death_mutex);
	return (0);
}

int	check_all_eaten(t_tous *p)
{
	int	all_eaten;
	int	i;

	all_eaten = 1;
	i = 0;
	while (i < p->count_ph)
	{
		pthread_mutex_lock(&p->death_mutex);
		if (p->philo[i].count_eating < p->count_must_eat)
		{
			all_eaten = 0;
			pthread_mutex_unlock(&p->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->death_mutex);
		i++;
	}
	return (all_eaten);
}

int	check_action_1(t_tous *p)
{
	if (p->count_must_eat != -1)
		p->all_eaten = check_all_eaten(p);
	pthread_mutex_lock(&p->death_mutex);
	if ((p->count_must_eat != -1 && p->all_eaten) || p->dead)
	{
		pthread_mutex_unlock(&p->death_mutex);
		stop_simulation(p);
		return (1);
	}
	pthread_mutex_unlock(&p->death_mutex);
	return (0);
}

void	*check_action(void *s)
{
	t_tous	*p;
	int		i;

	p = (t_tous *)s;
	while (1)
	{
		if (p->count_ph == 1)
			return (NULL);
		i = 0;
		while (i < p->count_ph)
		{
			if (check_death(&p->philo[i]))
			{
				stop_simulation(p);
				return (NULL);
			}
			i++;
		}
		if (check_action_1(p))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	thinking(t_ph *philo)
{
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->common->print);
	printf("%ld %d is thinking\n",
		get_time() - philo->common->start_process, philo->index);
	pthread_mutex_unlock(&philo->common->print);
	usleep(1000);
	return (0);
}
