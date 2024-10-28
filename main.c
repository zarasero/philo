/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:16:14 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/25 17:46:14 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_tous	p;

	if (ft_check(argc, argv))
		return (1);
	if (init_tous(argc, argv, &p))
		return (1);
	init_mutex(&p);
	init_philos(&p);
	init_thread(&p);
	ft_exit_success(&p);
	return (0);
}

void	stop_simulation(t_tous *p)
{
	pthread_mutex_lock(&p->print);
	pthread_mutex_lock(&p->death_mutex);
	p->stop = 1;
	p->dead = 1;
	pthread_mutex_unlock(&p->death_mutex);
	pthread_mutex_unlock(&p->print);
}

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
/*tv_sec — количество секунд с 1 января 1970 года (эпоха Unix).
tv_usec — количество микросекунд, прошедших с последней полной секунды.
Умножаем секунды на 1000, чтобы получить миллисекунды, и делим 
микросекунды на 1000, чтобы перевести их в миллисекунды.*/
