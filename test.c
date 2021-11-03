#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// void *print()
// {
// 	// pthread_t t[] = pthread_self();

// 	// usleep(1000);
// 	// pthread_mutex_lock(&mutex);
// 	// int ind = *(int *)arg;
// 	// pthread_t t1 = pthread_self();
// 	for (int i = 0; i < 15; i++)
// 	{
// 		printf("%s\n", "qqqaaaaaqdqdsfhsfdmhgfsgfsjg");
// 		usleep(50);
// 	}
// 	// pthread_mutex_unlock(&mutex);
// 	// free(arg);

// 	return (NULL);
// }

int main()
{
	// pthread_t t1;
	// pthread_t t2;

	// pthread_create(&t1, NULL, print, NULL);
	// pthread_create(&t2, NULL, print, NULL);
	// printf("t1 = %p\n", t1);
	// printf("t2 = %p\n", t2);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);

	struct timeval start, end, res;
	gettimeofday(&start, NULL);
	usleep(200 * 1000);
	gettimeofday(&end, NULL);
	res.tv_sec = end.tv_sec - start.tv_sec;
	res.tv_usec = end.tv_usec - start.tv_usec;
	if(res.tv_usec < 0)
	{
		res.tv_sec--;
		res.tv_usec += 1000;
	}
	int a = res.tv_sec * 1000 + res.tv_usec / 1000;
	printf("a = %d\n", a);

	write(1, "Exit\n", 5);
	return (0);
	}
