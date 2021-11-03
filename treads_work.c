/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:18:32 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/03 13:38:37 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philosophers *a, int i)
{
	int t = 0;
	// t = time_print(a);

	if (i == LEFT_FORK)
		printf("%d [ %d ] has taken a fork\n", t, a->id);
	else if (i == RIGHT_FORK)
		printf("%d [ %d ] has taken a fork\n", t, a->id);
	else if (i == EATS)
		printf("%d [ %d ] is eating\n", t, a->id);
	else if (i == SLEEPS)
		printf("%d [ %d ] is sleeping\n", t, a->id);
	else if (i == THINKS)
		printf("%d [ %d ] is thinking\n", t, a->id);
	else if (i == DIED)
		printf("%d [ %d ] died\n", t, a->id);
	i++;
}

// struct timeval take_time(void)
// {
// 	struct timeval t;

// 	gettimeofday(&t, NULL);
// 	return (t);
// }
// int time_print(t_philosophers *a)
// {
// 	a->time_for_philo->res.tv_sec = a->time_for_philo->end.tv_sec - a->time_for_philo->start.tv_sec;
// 	a->time_for_philo->res.tv_usec = a->time_for_philo->end.tv_usec - a->time_for_philo->start.tv_usec;
// 	if (a->time_for_philo->res.tv_usec  < 0)
// 	{
// 		a->time_for_philo->res.tv_sec--;
// 		a->time_for_philo->res.tv_usec  += 1000;
// 	}
// 	int time = a->time_for_philo->res.tv_sec  * 1000 + a->time_for_philo->res.tv_usec  / 1000;
// 	return (time);
// }

void *treads_work(void *arguments)
{
	t_philosophers *a;
	a = (t_philosophers *)arguments;

	pthread_mutex_lock(a->left);
	a->status = 1;
	print_status(a, a->status);
	pthread_mutex_lock(a->right);
	a->status = 2;
	print_status(a, a->status);
	a->status = 3;
	print_status(a, a->status);
	usleep(a->for_philo->time_to_eat * 1000);
	a->status = 4;
	print_status(a, a->status);
	pthread_mutex_unlock(a->right);
	pthread_mutex_unlock(a->left);
	usleep(a->for_philo->time_to_sleep * 1000);
	a->status = 5;
	print_status(a, a->status);

	return (NULL);
}
