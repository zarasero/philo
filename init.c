/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:45:01 by zserobia          #+#    #+#             */
/*   Updated: 2024/10/02 19:45:46 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_tous *p)
{
	int	i;

	i = 0;
	while (i < p->count_ph)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&p->print, NULL);
	pthread_mutex_init(&p->death_mutex, NULL);
}

void	init_thread_cont(t_tous *p)
{
	int	i;

	i = 0;
	while (i < p->count_ph)
	{
		pthread_join(p->thr[i], NULL);
		i++;
	}
	pthread_join(p->check_thread, NULL);
}

void	init_thread(t_tous *p)
{
	int	i;

	i = 0;
	p->start_process = get_time();
	while (i < p->count_ph)
	{
		pthread_create(&p->thr[i], NULL, act, (void *) &p->philo[i]);
		i++;
	}
	pthread_create(&p->check_thread, NULL, check_action, (void *) p);
	init_thread_cont(p);
}

int	init_tous(int argc, char **argv, t_tous *p)
{
	p->count_ph = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->count_must_eat = ft_atoi(argv[5]);
	else
		p->count_must_eat = -1;
	p->dead = 0;
	p->stop = 0;
	p->all_eaten = 1;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->count_ph);
	p->thr = malloc(sizeof(pthread_t) * p->count_ph);
	p->philo = malloc(sizeof(t_ph) * p->count_ph);
	if (!p->forks || !p->thr || !p->philo)
	{
		printf("Memory allocation failed\n");
		exit_free(p);
		return (1);
	}
	return (0);
}

void	init_philos(t_tous *p)
{
	int	i;

	i = 0;
	while (i < p->count_ph)
	{
		p->philo[i].index = i + 1;
		p->philo[i].count_eating = 0;
		p->philo[i].l_fork = &p->forks[i];
		p->philo[i].r_fork = &p->forks[(i + 1) % p->count_ph];
		p->philo[i].common = p;
		p->philo[i].last_eat = get_time();
		i++;
	}
}
