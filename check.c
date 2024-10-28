/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:26:53 by zserobia          #+#    #+#             */
/*   Updated: 2024/09/25 17:26:57 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_1(int argc, char **argv)
{
	int	i;
	int	y;

	i = 1;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y])
		{
			if (!ft_isdigit(argv[i][y]))
			{
				printf("Invalid argument: %s\n", argv[i]);
				return (1);
			}
			y++;
		}
		i++;
	}
	return (0);
}

int	ft_check_2(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Invalid count philo");
		return (1);
	}
	if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		printf("Invalid argument");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
	{
		printf("Invalid argument");
		return (1);
	}
	return (0);
}

int	ft_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid argument count: %d\n", argc);
		return (1);
	}
	if (ft_check_1(argc, argv))
		return (1);
	if (ft_check_2(argc, argv))
		return (1);
	return (0);
}
