/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:51:35 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/27 15:32:30 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_waiter(t_philosophers *philo)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, waiter_work, (void *) philo))
		return (-1);
	if (pthread_join(waiter, NULL))
		return (-1);
	return (0);
}

int	eating_count(t_philosophers *a, int num)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < num - 1)
	{
		if (a[i].count_how_many_eat == a[i + 1].count_how_many_eat)
			count++;
		else
			return (0);
		i++;
	}
	return (1);
}

int	monitor(t_philosophers *w, int a, int i)
{
	if ((((int)(get_time_msec() - w[i].time_last_eat))
		> w[i].for_philo->time_to_die))
	{
		print_status((int)(get_time_msec()
				- w[i].for_philo->time_start), &w[i], DIED);
		return (1);
	}
	if (eating_count(w, a) && w->for_philo->num_each != -1)
	{
		if (w[a - 1].count_how_many_eat >= w->for_philo->num_each)
			return (1);
	}
	return (0);
}

void	*waiter_work(void *arg)
{
	t_philosophers	*w;
	int				i;
	int				a;

	w = (t_philosophers *)arg;
	a = w->for_philo->num_of_philo;
	while (1)
	{
		i = -1;
		while (++i < a)
		{
			if (monitor(w, a, i))
				return (NULL);
		}
	}
	return (NULL);
}
