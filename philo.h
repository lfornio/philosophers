/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/10/29 13:48:45 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

#define LEFT_FORK 1
#define RIGHT_FORK 2
#define EATS 3
#define SLEEPS 4
#define THINKS 5
#define DIED 6


typedef struct s_arg
{
	int num_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_each;
	int num_of_fork;
	pthread_mutex_t *mutex;
	char *mutex_condition;
	int *philo_condition;
} t_arg;

int	f_atoi(const char *str);
long long	long_atoi(const char *str);


#endif
