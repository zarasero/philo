/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:21:39 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/25 17:21:42 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_ph
{
	int				index;
	int				count_eating;
	time_t			last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_tous	*common;
}	t_ph;

typedef struct s_tous
{
	int				count_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_must_eat;
	int				dead;
	int				stop;
	int				all_eaten;
	time_t			start_process;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_mutex;
	pthread_t		*thr;
	pthread_t		check_thread;
	t_ph			*philo;
}	t_tous;

int		main(int argc, char **argv);
int		init_tous(int argc, char **argv, t_tous *p);
void	init_mutex(t_tous *p);
void	init_thread(t_tous *p);
void	init_philos(t_tous *p);
int		ft_check_1(int argc, char **argv);
int		ft_check_2(int argc, char **argv);
int		ft_check(int argc, char **argv);
int		check_death(t_ph *philo);
void	*check_action(void *s);
void	*act(void *s);
int		take_forks(t_ph *philo);
int		eating(t_ph *philo);
int		sleeping(t_ph *philo);
int		thinking(t_ph *philo);
void	exit_free(t_tous *p);
int		ft_atoi(const char *str);
int		ft_isdigit(int a);
void	ft_exit_success(t_tous *p);
long	get_time(void);
void	print_message(t_ph *philo, const char *message);
void	stop_simulation(t_tous *p);
void	act_1_philo(t_ph *philo);
int		act_2(t_ph *philo);
void	init_thread_cont(t_tous *p);
int		check_all_eaten(t_tous *p);
int		check_action_1(t_tous *p);

#endif