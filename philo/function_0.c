/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:39:40 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/23 13:11:46 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	f_atoi(const char *str)
{
	long	i;
	long	n;
	int		b;

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

long long	long_atoi(const char *str)
{
	long	i;
	long	n;
	int		b;

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

int	error_arg(char *str)
{
	int	i;
	int	count;

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

long	get_time_msec(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	count_time(int a)
{
	long	end;
	long	time_now;

	end = get_time_msec() + a;
	time_now = get_time_msec();
	while (time_now < end)
	{
		usleep(50);
		time_now = get_time_msec();
	}
}
