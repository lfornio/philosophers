/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:18:32 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/27 15:38:24 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(int time, t_philosophers *a, int i)
{
	if (!pthread_mutex_lock(a->for_philo->lock))
	{
		if (i == LEFT_FORK)
			printf("%d %d has taken a fork\n", time, a->id);
		else if (i == RIGHT_FORK)
			printf("%d %d has taken a fork\n", time, a->id);
		else if (i == EATS)
			printf("%d %d is eating\n", time, a->id);
		else if (i == SLEEPS)
			printf("%d %d is sleeping\n", time, a->id);
		else if (i == THINKS)
			printf("%d %d is thinking\n", time, a->id);
		if (i == DIED)
		{
			printf("%d %d died\n", time, a->id);
			return (1);
		}
		pthread_mutex_unlock(a->for_philo->lock);
	}
	return (0);
}

void	status_eatinng(t_philosophers *a)
{
	print_status((int)(get_time_msec() - a->for_philo->time_start),
		a, LEFT_FORK);
	print_status((int)(get_time_msec() - a->for_philo->time_start),
		a, RIGHT_FORK);
	print_status((int)(get_time_msec() - a->for_philo->time_start),
		a, EATS);
}

void	*treads_work(void *arguments)
{
	t_philosophers	*a;

	a = (t_philosophers *)arguments;
	while (1)
	{
		if (!pthread_mutex_lock(a->left) && !pthread_mutex_lock(a->right))
		{
			a->time_last_eat = get_time_msec();
			a->count_how_many_eat++;
			status_eatinng(a);
			count_time(a->for_philo->time_to_eat);
			pthread_mutex_unlock(a->left);
			pthread_mutex_unlock(a->right);
		}
		print_status((int)(get_time_msec() - a->for_philo->time_start),
			a, SLEEPS);
		count_time(a->for_philo->time_to_sleep);
		print_status((int)(get_time_msec() - a->for_philo->time_start),
			a, THINKS);
	}
	return (NULL);
}
