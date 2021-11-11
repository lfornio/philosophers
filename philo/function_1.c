/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:41:44 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/11 13:24:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_lock(t_arguments *data)
{
	pthread_mutex_t	l;

	if (pthread_mutex_init(&l, NULL))
		return (-1);
	data->lock = &l;
	return (0);
}

void	destroy_forks(t_arguments *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(data->lock);
	while (++i < data->num_of_fork)
		pthread_mutex_destroy(&data->forks[i]);
}

void	init_start_time(t_arguments *data, t_philosophers *philo)
{
	int	i;

	i = -1;
	data->time_start = get_time_msec();
	while (++i < data->num_of_philo)
		philo[i].time_last_eat = get_time_msec();
}

int	create_treads(t_arguments *data, t_philosophers *philo)
{
	pthread_t	*philo_treads;
	int			i;

	i = -1;
	philo_treads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!philo_treads)
		return (-1);
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&philo_treads[i], NULL, treads_work,
				(void *)&philo[i]))
			return (-1);
		usleep(1);
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_detach(philo_treads[i]))
			return (-1);
	}
	data->philo_treads = philo_treads;
	return (0);
}

int	init_treads(t_arguments *data, t_philosophers *philo)
{
	init_start_time(data, philo);
	create_treads(data, philo);
	if (init_waiter(philo) < 0)
		return (-1);
	free(data->philo_treads);
	destroy_forks(data);
	return (0);
}
