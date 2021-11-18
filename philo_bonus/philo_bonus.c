/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 07:54:02 by lfornio           #+#    #+#             */
/*   Updated: 2021/11/18 16:00:18 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int error_arguments(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error arguments\n");
		return (-1);
	}
	while (i < argc)
	{
		if (error_arg(argv[i]) == 1 || long_atoi(argv[i]) > INT_MAX)
		{
			printf("Error argument\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int init_arguments(t_arguments *data, int argc, char **argv)
{
	data->num_of_philo = f_atoi(argv[1]);
	if (data->num_of_philo < 1)
	{
		printf("Error philosophers\n");
		return (-1);
	}
	data->time_to_die = f_atoi(argv[2]);
	data->time_to_eat = f_atoi(argv[3]);
	data->time_to_sleep = f_atoi(argv[4]);
	data->num_of_fork = data->num_of_philo;
	if (argc == 6)
		data->num_each = f_atoi(argv[5]);
	else
		data->num_each = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0 || data->num_each == 0)
		return (-1);
	return (0);
}

int main(int argc, char **argv)
{

	printf("PID основного процесса = %d\n", getpid());
	t_arguments data;

	if (error_arguments(argc, argv) < 0 || init_arguments(&data, argc, argv) < 0)
		return (1);
	data.array_pid = (int *)malloc(sizeof(int) * data.num_of_philo);
	if (!data.array_pid)
		return (1);
	int i;
	i = -1;
	while (++i < data.num_of_philo)
	{
		data.array_pid[i] = 0;
	}
	//------------------------------------------------
	printf("Массив pid в начале\n");
	for (int k = 0; k < data.num_of_philo; k++)
		printf("%d  ", data.array_pid[k]);
	printf("\n");
	//------------------------------------------------
	sem_t *forks;
	forks = sem_open("forks", O_CREAT | O_EXCL, 0600, data.num_of_fork);
	int pid;
	i = 0;
	data.time_start = get_time_msec();
	while (i < data.num_of_philo)
	{
		pid = fork();
		if (pid)
			data.array_pid[i] = pid;
		else if (!pid)
		{
			data.philosophers.i = i;
			data.philosophers.id = i + 1;
			data.philosophers.hungry = 0;
			data.philosophers.status = 0;
			data.philosophers.count_how_many_eat = 0;
			data.philosophers.time_last_eat = get_time_msec();
			// printf("PID процесса %d: родительский процесс %d\n", getpid(), getppid());
			break;
		}
		usleep(1);
		i++;
	}
	//------------------------------------------------
	if (pid)
	{
		printf("Массив pid\n");
		for (int k = 0; k < data.num_of_philo; k++)
			printf("%d  ", data.array_pid[k]);
		printf("\n");
	}
	//------------------------------------------------
	if (!pid)
	{
		while (1)
		{
			if (!sem_wait(forks) && !sem_wait(forks))
			{
				print_status((int)(get_time_msec() - data.time_start), data.philosophers.id, LEFT_FORK);
				print_status((int)(get_time_msec() - data.time_start), data.philosophers.id, RIGHT_FORK);
				print_status((int)(get_time_msec() - data.time_start), data.philosophers.id, EATS);
				data.philosophers.count_how_many_eat++;
				if ((data.philosophers.id == data.num_of_philo) && (data.philosophers.count_how_many_eat == data.num_each) && data.num_each != -1)
				{
					printf("END\n");
					// exit(1);
					pause();
				}
				data.philosophers.hungry = 1;
				data.philosophers.time_last_eat = get_time_msec();
				count_time(data.time_to_eat);
				sem_post(forks);
				sem_post(forks);
			}
			print_status((int)(get_time_msec() - data.time_start), data.philosophers.id, SLEEPS);
			data.philosophers.hungry = 0;
			count_time(data.time_to_sleep);
			print_status((int)(get_time_msec() - data.time_start), data.philosophers.id, THINKS);

			printf("i = %d, id = %d, hungry = %d, count_eat = %d\n", data.philosophers.i, data.philosophers.id,
				   data.philosophers.hungry, data.philosophers.count_how_many_eat);
		}
	}

	//------------------------------------------------


	// waitpid(-1)
	sem_unlink("forks");
	sem_close(forks);
	pause();
	return (0);
}
