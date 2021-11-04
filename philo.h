/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/04 16:16:09 by lfornio          ###   ########.fr       */
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
int flag;

typedef struct s_arguments
{
	int num_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_fork;
	int num_each;
	long long time_start;
	pthread_mutex_t *lock;
	// pthread_mutex_t *lock_2;
	pthread_mutex_t *forks;
} t_arguments;

typedef struct s_philosophers
{
	int i;
	int id;
	// int status;
	int left_fork;
	int right_fork;
	long long time_die;
	long long time_last_eat;
	// long long stop;
	int count_how_many_eat;
	int hungry;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	t_arguments *for_philo;

} t_philosophers;



int	f_atoi(const char *str);
long long	long_atoi(const char *str);
int error_arg(char *str);
void *treads_work(void *arguments);
long long get_time_msec(void);
void count_time(int a);
void *waiter_work(void *arg);
void print_status(int time, t_philosophers *a, int i);
// struct timeval take_time(void);
// int time_print(t_philosophers *a);


#endif
