#include "philo.h"

int main(int argc, char **argv)
{
	if(argc != 5 || argc != 6)
		printf("Error arguments\n");
	t_arg *data;
	data = (t_arg *)malloc(sizeof(t_arg));
	if(!data)
		return (1);
	int i = 1;   //проверка на max int, отрицательные числа, буквы
		while (i < argc)
		{
			if (error_arg(argv[i]) == 1 || long_atoi(argv[i]) > INT_MAX)
			{
				printf("Error argument\n");
				return (2);
			}
			i++;
		}
	data->num_of_philo = f_atoi(argv[1]);
	if (data->num_of_philo < 1)
		retrun(1);
	data->time_to_die = f_atoi(argv[2]);
	data->time_to_eat = f_atoi(argv[3]);
	data->time_to_sleep = f_atoi(argv[4]);
	if(argc == 6)
		data->count_eat_philo = f_atoi(argv[5]);
	else
		data->count_eat_philo = -1;

	if(data->count_eat_philo == 0)
		return(1);












	return (0);
}
