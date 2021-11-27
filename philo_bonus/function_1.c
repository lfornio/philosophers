/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:45:41 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/23 18:46:41 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_philo(t_arguments *data)
{
	int	a;
	int	status;
	int	j;
	int	i;

	a = waitpid(-1, &status, 0);
	if (WIFEXITED(status) == 1)
	{
		j = find_pid_in_array(data, a);
		i = 0;
		while (i < data->num_of_philo)
		{
			if (i < j || i > j)
				kill(data->array_pid[i], SIGKILL);
			i++;
		}
	}
}

int	find_pid_in_array(t_arguments *data, int a)
{
	int	i;

	i = 0;
	while (data->array_pid[i])
	{
		if (data->array_pid[i] == a)
			return (i);
		i++;
	}
	return (0);
}

int	init_array_pid(t_arguments *data)
{
	int	i;

	i = -1;
	data->array_pid = (int *)malloc(sizeof(int) * data->num_of_philo);
	if (!data->array_pid)
		return (-1);
	i = -1;
	while (++i < data->num_of_philo)
		data->array_pid[i] = 0;
	return (0);
}

void	print_status(int time, t_arguments *data, int i)
{
	sem_wait(data->lock);
	if (i == LEFT_FORK)
		printf("%d %d has taken a fork\n", time, data->philosophers.id);
	else if (i == RIGHT_FORK)
		printf("%d %d has taken a fork\n", time, data->philosophers.id);
	else if (i == EATS)
		printf("%d %d is eating\n", time, data->philosophers.id);
	else if (i == SLEEPS)
		printf("%d %d is sleeping\n", time, data->philosophers.id);
	else if (i == THINKS)
		printf("%d %d is thinking\n", time, data->philosophers.id);
	else if (i == DIED)
	{
		printf("%d %d died\n", time, data->philosophers.id);
		exit (1);
	}
	sem_post(data->lock);
}
