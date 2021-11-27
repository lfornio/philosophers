/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 07:54:02 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/23 13:00:42 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	main(int argc, char **argv)
{
	t_arguments	data;

	if (error_arguments(argc, argv) < 0
		|| init_arguments(&data, argc, argv) < 0)
		return (1);
	if (init_array_pid(&data) < 0)
		return (1);
	init_semafores(&data);
	data.time_start = get_time_msec();
	if (init_philosophers(&data) < 0)
		return (1);
	semaphores_end(&data);
	wait_philo(&data);
	return (0);
}
