/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/18 15:44:01 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>

# define LEFT_FORK 1
# define RIGHT_FORK 2
# define EATS 3
# define SLEEPS 4
# define THINKS 5
# define DIED 6

typedef struct s_philo
{
	int				i;
	int				id;
	int				status;
	int				count_how_many_eat;
	int				hungry;
	long long		time_last_eat;
}	t_philo;

typedef struct s_arguments
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_fork;
	int				num_each;
	long long		time_start;
	int				*array_pid;
	t_philo			philosophers;
}	t_arguments;


int			f_atoi(const char *str);
long long	long_atoi(const char *str);
int			error_arg(char *str);
int			error_arguments(int argc, char **argv);
int			init_arguments(t_arguments *data, int argc, char **argv);
long long	get_time_msec(void);
void		count_time(int a);
void	print_status(int time, int id, int i);
void	*waiter_work(void *arg);

#endif
