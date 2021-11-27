/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_and_waiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:43:44 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/23 18:44:41 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	waiter(t_arguments *data)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, waiter_work, (void *)data))
		return (-1);
	if (pthread_detach(waiter))
		return (-1);
	return (0);
}

void	*waiter_work(void *arg)
{
	t_arguments	*data;
	int			a;

	data = (t_arguments *)arg;
	a = data->num_of_philo;
	while (1)
	{
		sem_wait(data->lock_2);
		if ((((int)(get_time_msec() - data->philosophers.time_last_eat))
			> data->time_to_die) && data->philosophers.hungry == 0)
		{
			print_status((int)(get_time_msec() - data->time_start), data, DIED);
			usleep(50);
		}
		sem_post(data->lock_2);
	}
	return (NULL);
}

void	init_semafores(t_arguments *data)
{
	sem_t	*forks;
	sem_t	*lock;
	sem_t	*lock_2;

	forks = sem_open("forks", O_CREAT | O_EXCL, 0600, data->num_of_fork);
	data->forks = forks;
	lock = sem_open("lock", O_CREAT | O_EXCL, 0600, 1);
	data->lock = lock;
	lock_2 = sem_open("lock_2", O_CREAT | O_EXCL, 0600, 1);
	data->lock_2 = lock_2;
}

void	semaphores_end(t_arguments *data)
{
	sem_unlink("forks");
	sem_close(data->forks);
	sem_unlink("lock");
	sem_close(data->lock);
	sem_unlink("lock_2");
	sem_close(data->lock_2);
}
