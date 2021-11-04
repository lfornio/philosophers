/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:18:32 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/04 16:31:38 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(int time, t_philosophers *a, int i)
{
	// int t = 0;
	// // t = time_print(a);
	pthread_mutex_lock(a->for_philo->lock);
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
	else if (i == DIED)
		printf("%d %d died\n", time, a->id);
	// i++;
	pthread_mutex_unlock(a->for_philo->lock);

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

	while (1)
	{
		// if(!(a->id % 2))
		// 	usleep(100);
		// if (pthread_mutex_lock(a->left);
		if (!pthread_mutex_lock(a->left) && !pthread_mutex_lock(a->right))
{
		// print_status((int)(get_time_msec() - a->for_philo->time_start), a, a->status);
		print_status((int)(get_time_msec() - a->for_philo->time_start), a, LEFT_FORK);
		// pthread_mutex_lock(a->right);
		print_status((int)(get_time_msec() - a->for_philo->time_start), a, RIGHT_FORK);

		print_status((int)(get_time_msec() - a->for_philo->time_start), a, EATS);
		a->count_how_many_eat++;
		// if(a->count_how_many_eat == a->for_philo->num_each)
		// 	a->stop = get_time_msec() + a->for_philo->time_to_eat;
		count_time(a->for_philo->time_to_eat);
		a->hungry = 1;
		a->time_last_eat = get_time_msec();


		// a->time_die = get_time_msec() + (long long)a->for_philo->time_to_die;
		pthread_mutex_unlock(a->right);
		pthread_mutex_unlock(a->left);
}

		print_status((int)(get_time_msec() - a->for_philo->time_start), a, SLEEPS);

		count_time(a->for_philo->time_to_sleep);
		a->hungry = 0;
		print_status((int)(get_time_msec() - a->for_philo->time_start), a, THINKS);
	}
	return (NULL);
}
