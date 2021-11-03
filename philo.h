/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/03 13:40:13 by lfornio          ###   ########.fr       */
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
#include <sys/time.h>

#define LEFT_FORK 1
#define RIGHT_FORK 2
#define EATS 3
#define SLEEPS 4
#define THINKS 5
#define DIED 6

// typedef struct s_time
// {
// 	struct timeval start;
// 	struct timeval end;
// 	struct timeval res;
// } t_time;

typedef struct s_arguments
{
	int num_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_fork;
	int num_each;
	pthread_mutex_t *forks;
} t_arguments;

typedef struct s_philosophers
{
	int i;
	int id;
	int status;
	int left_fork;
	int right_fork;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	t_arguments *for_philo;

} t_philosophers;



int	f_atoi(const char *str);
long long	long_atoi(const char *str);
int error_arg(char *str);
void *treads_work(void *arguments);
// struct timeval take_time(void);
// int time_print(t_philosophers *a);


#endif
