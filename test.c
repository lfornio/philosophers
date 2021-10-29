#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print()
{
	// pthread_t t[] = pthread_self();

	// usleep(1000);
	// pthread_mutex_lock(&mutex);
	// int ind = *(int *)arg;
	// pthread_t t1 = pthread_self();
	for (int i = 0; i < 15; i++)
	{
		printf("%s\n", "qqqaaaaaqdqdsfhsfdmhgfsgfsjg");
		sleep(1);
	}
	// pthread_mutex_unlock(&mutex);
	// free(arg);

	return (NULL);
}

int main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, print, NULL);
	pthread_create(&t2, NULL, print, NULL);
	printf("t1 = %p\n", t1);
	printf("t2 = %p\n", t2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

		// pthread_mutex_init(&mutex, NULL);
		// int i = 0;
		// while(i < num)
		// {
		// 	int *p = malloc(sizeof(int));
		// 	*p = i;
		// 	if (pthread_create(&t[i], NULL, print, p) != 0)
		// 		return (1);
		// 	// printf("start %d\n", i);
		// 	i++;
		// }
		// i = 0;
		// while(i < num)
		// {
		// 	if(pthread_join(t[i], NULL))
		// 		return (2);
		// 	// printf("done %d\n", i);
		// 	i++;
		// }
		// // pthread_mutex_destroy(&mutex);
		write(1, "Exit\n", 5);
		return (0);
	}
