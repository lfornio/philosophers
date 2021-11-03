/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 07:54:02 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/03 14:39:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error arguments\n");
		return (1);
	}
	int i = 1; //проверка на max int, отрицательные числа, буквы
	while (i < argc)
	{
		if (error_arg(argv[i]) == 1 || long_atoi(argv[i]) > INT_MAX)
		{
			printf("Error argument\n");
			return (1);
		}
		i++;
	}

	t_arguments data;
	// t_time time;
	data.num_of_philo = f_atoi(argv[1]);
	if (data.num_of_philo < 1)
	{
		printf("Error philosophers\n");
		return (1);
	}
	data.time_to_die = f_atoi(argv[2]);
	data.time_to_eat = f_atoi(argv[3]);
	data.time_to_sleep = f_atoi(argv[4]);
	data.num_of_fork = data.num_of_philo;
	if (argc == 6)
		data.num_each = f_atoi(argv[5]);
	else
		data.num_each = -1;

	t_philosophers *philo;
	philo = (t_philosophers *)malloc(sizeof(t_philosophers) * data.num_of_philo);
	if (!philo)
		return(1);
	i = 0;
	while (i < data.num_of_philo)
	{
		philo[i].i = i;
		philo[i].id = i + 1;
		philo[i].status = 0;
		philo[i].for_philo = &data;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data.num_of_fork;
		// philo[i].time_for_philo = &time;
		i++;
	}

	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.num_of_fork);
	if(!data.forks)
		return (1);
	i = 0;
	while(i < data.num_of_fork)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	i = 0;
	while(i < data.num_of_fork)
	{
		philo[i].left = &data.forks[philo[i].left_fork];
		philo[i].right = &data.forks[philo[i].right_fork];
		i++;
	}



	pthread_t *philo_treads;
	philo_treads = (pthread_t *)malloc(sizeof(pthread_t) * data.num_of_philo);
	if(!philo_treads)
		return (1);
	i = 0;
	// data.time->start = take_time();
	while(i < data.num_of_philo)
	{
		pthread_create(&philo_treads[i], NULL, treads_work, (void *)&philo[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while(i < data.num_of_philo)
	{
		pthread_join(philo_treads[i], NULL);
		i++;
	}


	// i = 0;                   //печать структур
	// while(i < data.num_of_philo)
	// {
	// 	printf("ptr_philo = %p\n", &philo[i]);
	// 	printf("%d: i = %d\n", i, philo[i].i);
	// 	printf("%d: id = %d\n", i, philo[i].id);
	// 	printf("%d: for_philo = %p\n", i, philo[i].for_philo);
	// 	printf("%d: num_ph = %d\n", i, philo[i].for_philo->num_of_philo);
	// 	printf("%d: time_die = %d\n", i, philo[i].for_philo->time_to_die);
	// 	printf("%d: time_eat = %d\n", i, philo[i].for_philo->time_to_eat);
	// 	printf("%d: time_sleep = %d\n", i, philo[i].for_philo->time_to_sleep);
	// 	printf("%d: num_fork = %d\n", i, philo[i].for_philo->num_of_fork);
	// 	printf("%d: left_fork = %d\n", i, philo[i].left_fork);
	// 	printf("%d: left = %p\n", i, philo[i].left);
	// 	printf("%d: right_fork = %d\n", i, philo[i].right_fork);
	// 	printf("%d: right = %p\n", i, philo[i].right);
	// 	printf("%d: num_each = %d\n",i, philo[i].for_philo->num_each);
	// 	printf("\n");
	// 	i++;
	// }

	return (0);
}
