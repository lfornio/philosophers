/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:51:35 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/04 16:38:40 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *waiter_work(void *arg)
{
	t_philosophers *w;
	w = (t_philosophers *)arg;
	int i;
	int a;
	int count;
	a = w->for_philo->num_of_philo;
	count = w->for_philo->num_each;
	// int j = 0;

	// i = 0;
	while (1)
	{
		i = 0;
		while (i < a)
		{
				// if (w[i].count_how_many_eat == count)
				// 	// j++;
				// usleep(100);
				// if ((get_time_msec() > w[i].time_die))
				if((((int)(get_time_msec() - w[i].time_last_eat)) > w[i].for_philo->time_to_die) && w[i].hungry == 0)
				{
					print_status((int)(get_time_msec() - w[i].for_philo->time_start), &w[i], DIED);
					// usleep(10);
					return (NULL);
				}
				// if(i == 3 && get_time_msec() == w[i].stop)
				// {
				// 	usleep(50);
				// 	printf("end\n");


				// 	return (NULL);
				// }
				if(i == a - 1 && w[i].count_how_many_eat == count)
					{
							// printf("end\n");
							// usleep(100);
							return (NULL);
					}



				// if (i == 3)
				// 	printf("nun %d = %d\n", w[i].id, w[i].count_how_many_eat);
				// if((i == w[i].for_philo->num_of_philo - 1) && (w[i].count_how_many_eat == w[i].for_philo->num_each))
				// 	return (NULL);

			i++;
		}
		// usleep(100);


	}
	return (NULL);
}
