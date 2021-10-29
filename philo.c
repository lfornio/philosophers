/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:28:48 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/29 14:14:30 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_arr(int *arr, t_arg *arg)
{
	int i = 0;
	while (i < arg->num_of_philo)
	{
		printf("%d ", arr[i]);

		i++;
	}
	printf("\n");
}

int error_arg(char *str)
{
	int i;
	int count;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			count++;
		else
			return (1);
		i++;
	}
	return (0);
}

void init_arg_null(t_arg *arg)
{
	arg->num_of_philo = 0;
	arg->time_to_die = 0;
	arg->time_to_eat = 0;
	arg->time_to_sleep = 0;
	arg->num_each = -1;
	arg->num_of_fork = 0;
}

void print(t_arg *b, int i)
{

	if (b->philo_condition[i] == LEFT_FORK)
		printf("[ %d ] has taken a fork\n", i + 1);
	else if (b->philo_condition[i] == RIGHT_FORK)
		printf("[ %d ] has taken a fork\n", i + 1);
	else if (b->philo_condition[i] == EATS)
		printf("[ %d ] is eating\n", i + 1);
	else if (b->philo_condition[i] == SLEEPS)
		printf("[ %d ] is sleeping\n", i + 1);
	else if (b->philo_condition[i] == DIED)
		printf("[ %d ] died\n", i);
	i++;

}

void *func(void *arg)
{
	t_arg *a = (t_arg *)arg;
	static int i = 0;
	// i = i + 2;

	// usleep(50);
	// int i = 0;

	if (a->mutex_condition[i] == '0' && a->mutex_condition[(i + 1) % a->num_of_fork] == '0')
	{
		pthread_mutex_lock(&a->mutex[i]);
		pthread_mutex_lock(&a->mutex[(i + 1) % a->num_of_fork]);
		a->mutex_condition[i] = '1';
		a->philo_condition[i] = 1;
		print(a, i);
		// print_arr(a->philo_condition, arg);
		a->mutex_condition[(i + 1) % a->num_of_fork] = '1';
		a->philo_condition[i] = 2;
		print(a, i);
		// print_arr(a->philo_condition, arg);
		a->philo_condition[i] = 3;
		print(a, i);
		// print_arr(a->philo_condition, arg);
		// printf("mutex = %s\n", a->mutex_condition);
	}
	i = i + 2;

	// printf("i =  %d\n", i);

	// if (a->mutex_condition[i] == '0' && a->mutex_condition[(i + 1) % a->num_of_fork] == '0')
	// {

	// 	pthread_mutex_lock(&a->mutex[i]);
	// 	pthread_mutex_lock(&a->mutex[(i + 1) % a->num_of_fork]);
	// 	a->mutex_condition[i] = '1';
	// 	a->mutex_condition[(i + 1) % a->num_of_fork] = '1';
	// 	printf("str3 =  %s\n", a->mutex_condition);
	// }

	sleep(3);
	return (NULL);
}

int main(int argc, char **argv)
{

	if (argc == 5 || argc == 6)
	{
		t_arg *arg;
		arg = (t_arg *)malloc(sizeof(t_arg));
		if (!arg)
			return (1);
		int i = 1;
		while (i < argc)
		{
			if (error_arg(argv[i]) == 1 || long_atoi(argv[i]) > INT_MAX)
			{
				printf("Error argument\n");
				return (2);
			}
			i++;
		}
		init_arg_null(arg);
		arg->num_of_philo = f_atoi(argv[1]);
		arg->time_to_die = f_atoi(argv[2]);
		arg->time_to_eat = f_atoi(argv[3]);
		arg->time_to_sleep = f_atoi(argv[4]);
		arg->num_of_fork = arg->num_of_philo;
		if (argc == 6)
			arg->num_each = f_atoi(argv[5]);
		if (arg->num_of_philo == 1)
		{
			printf("Only one philosopher and one fork\n");
			return (3);
		}
		if (arg->num_of_philo % 2 == 0)
		{
			pthread_t ph[arg->num_of_philo];
			// pthread_t state;
			arg->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->num_of_fork);
			i = 0;
			while (i < arg->num_of_fork)
			{
				pthread_mutex_init(&arg->mutex[i], NULL);
				printf("mutex =  %p\n", &arg->mutex[i]);
				i++;
			}
			arg->mutex_condition = (char *)malloc(sizeof(char) * arg->num_of_fork);
			if (!arg->mutex_condition)
				return (4);
			arg->mutex_condition = memset(arg->mutex_condition, '0', arg->num_of_fork);
			arg->philo_condition = (int *)malloc(sizeof(int) * arg->num_of_philo);
			if (!arg->philo_condition)
				return (5);
			i = 0;
			while (i < arg->num_of_philo)
			{
				arg->philo_condition[i] = 0;
				i++;
			}
			// print_arr(arg->philo_condition, arg);
			// pthread_create(&state, NULL, print, (void *)arg);
			// pthread_detach(state);
			i = 0;
			while (i < arg->num_of_philo)
			{
				pthread_create(&ph[i], NULL, func, (void *)arg);
				printf("create %d\n", i);
				i += 2;
				usleep(50);
			}

			i = 0;
			while (i < arg->num_of_philo)
			{
				pthread_join(ph[i], NULL);
				i += 2;
			}

			printf("/2\n");
		}
		else
		{
			printf("no /2\n");
		}
		printf("str2 =  %s\n", arg->mutex_condition);
		printf("OK\n");
	}
	else
	{
		printf("Error argument\n");
	}

	return (0);
}
