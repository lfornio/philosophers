/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 07:54:02 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/11 12:50:43 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error arguments\n");
		return (-1);
	}
	while (i < argc)
	{
		if (error_arg(argv[i]) == 1 || long_atoi(argv[i]) > INT_MAX)
		{
			printf("Error argument\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_arguments(t_arguments *data, int argc, char **argv)
{
	data->num_of_philo = f_atoi(argv[1]);
	if (data->num_of_philo < 1)
	{
		printf("Error philosophers\n");
		return (-1);
	}
	data->time_to_die = f_atoi(argv[2]);
	data->time_to_eat = f_atoi(argv[3]);
	data->time_to_sleep = f_atoi(argv[4]);
	data->num_of_fork = data->num_of_philo;
	if (argc == 6)
		data->num_each = f_atoi(argv[5]);
	else
		data->num_each = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->num_each == 0)
		return (-1);
	return (0);
}

void	init_philosophers(t_philosophers *philo, t_arguments *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		philo[i].i = i;
		philo[i].id = i + 1;
		philo[i].for_philo = data;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->num_of_fork;
		philo[i].count_how_many_eat = 0;
		philo[i].hungry = 0;
	}
}

int	init_forks(t_arguments *data, t_philosophers *philo)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_fork);
	if (!data->forks)
		return (-1);
	while (++i < data->num_of_fork)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
	}
	while (++j < data->num_of_fork)
	{
		philo[j].left = &data->forks[philo[j].left_fork];
		philo[j].right = &data->forks[philo[j].right_fork];
	}
	if (init_lock(data) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments		data;
	t_philosophers	*philo;

	if (error_arguments(argc, argv) < 0
		|| init_arguments(&data, argc, argv) < 0)
		return (1);
	philo = (t_philosophers *)malloc(sizeof(t_philosophers)
			* data.num_of_philo);
	if (!philo)
		return (1);
	init_philosophers(philo, &data);
	if (init_forks(&data, philo) < 0)
		return (1);
	if (init_treads(&data, philo) < 0)
		return (1);
	return (0);
}
