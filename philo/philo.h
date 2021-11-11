/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:46:08 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/11 13:46:23 by lfornio          ###   ########.fr       */
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
# include <sys/time.h>

# define LEFT_FORK 1
# define RIGHT_FORK 2
# define EATS 3
# define SLEEPS 4
# define THINKS 5
# define DIED 6

typedef struct s_arguments
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_fork;
	int				num_each;
	long long		time_start;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*forks;
	pthread_t		*philo_treads;
}	t_arguments;

typedef struct s_philosophers
{
	int				i;
	int				id;
	int				left_fork;
	int				right_fork;
	long long		time_die;
	long long		time_last_eat;
	int				count_how_many_eat;
	int				hungry;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_arguments		*for_philo;
}	t_philosophers;

int			f_atoi(const char *str);
long long	long_atoi(const char *str);
int			error_arg(char *str);
void		*treads_work(void *arguments);
long long	get_time_msec(void);
void		count_time(int a);
void		*waiter_work(void *arg);
void		print_status(int time, t_philosophers *a, int i);
int			error_arguments(int argc, char **argv);
int			init_arguments(t_arguments *data, int argc, char **argv);
void		init_philosophers(t_philosophers *philo, t_arguments *data);
int			init_lock(t_arguments *data);
int			init_forks(t_arguments *data, t_philosophers *philo);
int			init_waiter(t_philosophers *philo);
void		destroy_forks(t_arguments *data);
int			init_treads(t_arguments *data, t_philosophers *philo);

#endif
