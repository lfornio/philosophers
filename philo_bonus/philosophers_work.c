/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_work.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:48:06 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/23 13:03:53 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philosophers(t_arguments *data)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < data->num_of_philo)
	{
		pid = fork();
		error_pid(pid);
		if (pid)
			data->array_pid[i] = pid;
		else if (!pid)
		{
			pack_struct(data, i);
			break ;
		}
		usleep(1);
	}
	if (!pid)
	{
		if (waiter(data) < 0)
			return (-1);
		philosophers_work(data);
	}
	return (0);
}

int	error_pid(int pid)
{
	if (pid == -1)
	{
		printf("Error fork()\n");
		return (-1);
	}
	return (0);
}

void	pack_struct(t_arguments *data, int i)
{
	data->philosophers.i = i;
	data->philosophers.id = i + 1;
	data->philosophers.hungry = 0;
	data->philosophers.status = 0;
	data->philosophers.count_how_many_eat = 0;
	data->philosophers.status = 0;
	data->philosophers.time_last_eat = get_time_msec();
}

void	philosophers_work(t_arguments *data)
{
	while (1)
	{
		eating(data);
		print_status((int)(get_time_msec() - data->time_start), data, SLEEPS);
		data->philosophers.hungry = 0;
		count_time(data->time_to_sleep);
		print_status((int)(get_time_msec() - data->time_start), data, THINKS);
	}
}

void	eating(t_arguments *data)
{
	if (!sem_wait(data->forks) && !sem_wait(data->forks))
	{
		data->philosophers.time_last_eat = get_time_msec();
		print_status((int)(get_time_msec() - data->time_start),
			data, LEFT_FORK);
		print_status((int)(get_time_msec() - data->time_start),
			data, RIGHT_FORK);
		print_status((int)(get_time_msec() - data->time_start), data, EATS);
		data->philosophers.count_how_many_eat++;
		if ((data->philosophers.id == data->num_of_philo)
			&& (data->philosophers.count_how_many_eat == data->num_each)
			&& (data->num_each != -1))
			exit(1);
		count_time(data->time_to_eat);
		sem_post(data->forks);
		sem_post(data->forks);
	}
}
