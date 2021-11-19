/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:39:40 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/19 17:36:33 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int f_atoi(const char *str)
{
	long i;
	long n;
	int b;

	i = 0;
	n = 0;
	b = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			b = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	n = n * b;
	return (n);
}

long long long_atoi(const char *str)
{
	long i;
	long n;
	int b;

	i = 0;
	n = 0;
	b = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			b = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	n = n * b;
	return (n);
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

long get_time_msec(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void count_time(int a)
{
	long end;
	long time_now;

	end = get_time_msec() + a;
	time_now = get_time_msec();
	while (time_now < end)
	{
		usleep(50);
		time_now = get_time_msec();
	}
}

void print_status(int time, t_arguments *data, int i)
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
		printf("%d %d died\n", time, data->philosophers.id);
	sem_post(data->lock);
}

int find_pid_in_array(t_arguments *data, int a)
{
	int i;
	i = 0;
	while (data->array_pid[i])
	{
		if (data->array_pid[i] == a)
			return (i);
		i++;
	}
	return (0);
}

void wait_philo(t_arguments *data)
{
	int a;
	int status;
	int j;
	int i;

	a = waitpid(-1, &status, 0);
	// 	printf("a = %d\n", a);
	// 	printf("status = %d\n", status);
	if (a < 0)
		printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	if (WIFEXITED(status) == 1)
	{

		// printf("COOL\n");
		j = find_pid_in_array(data, a);
		// printf("j = %d\n", j);
		i = 0;
		while (i < data->num_of_philo)
		{
			if (i < j || i > j)
			{
				kill(data->array_pid[i], SIGKILL);
				// printf("kill %d\n", i);
			}

			i++;
		}
	}
	// 	// printf("OK\n");
	// 	// pause();
}

void *waiter_work(void *arg)
{
	t_arguments *data;
	int a;

	data = (t_arguments *)arg;
	a = data->num_of_philo;
	while (1)
	{
		sem_wait(data->lock_2);
		if ((((int)(get_time_msec() - data->philosophers.time_last_eat)) > data->time_to_die) && data->philosophers.hungry == 0)
		{
			print_status((int)(get_time_msec() - data->time_start), data, DIED);
			usleep(50);
			exit(1);
			// data->philosophers.status = 1;
		}
		sem_post(data->lock_2);
	}
	return (NULL);
}
