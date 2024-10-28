/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:29:19 by zserobia          #+#    #+#             */
/*   Updated: 2024/10/10 18:29:22 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_ph *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->index % 2 == 0)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(first_fork);
	print_message(philo, "has taken a fork");
	if (check_death(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	print_message(philo, "has taken a fork");
	return (0);
}

void	print_message(t_ph *philo, const char *message)
{
	pthread_mutex_lock(&philo->common->death_mutex);
	if (philo->common->dead)
	{
		pthread_mutex_unlock(&philo->common->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->common->death_mutex);
	pthread_mutex_lock(&philo->common->print);
	printf("%ld %d %s\n", get_time() - philo->common->start_process,
		philo->index, message);
	pthread_mutex_unlock(&philo->common->print);
}

int	eating(t_ph *philo)
{
	pthread_mutex_lock(&philo->common->print);
	printf("%ld %d is eating\n", get_time() - philo->common->start_process,
		philo->index);
	pthread_mutex_unlock(&philo->common->print);
	pthread_mutex_lock(&philo->common->death_mutex);
	philo->last_eat = get_time();
	philo->count_eating++;
	pthread_mutex_unlock(&philo->common->death_mutex);
	usleep(philo->common->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	sleeping(t_ph *philo)
{
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->common->print);
	printf("%ld %d is sleeping\n", get_time() - philo->common->start_process,
		philo->index);
	pthread_mutex_unlock(&philo->common->print);
	usleep(philo->common->time_to_sleep * 1000);
	return (0);
}
