#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>

int main()
{
	printf("PID = %d\n", getpid());
	int n = 5;
	int i = 0;
	sem_t *sem;
	sem = sem_open("sem", O_CREAT | O_EXCL, 0600, 5);
	printf("sem = %p\n", sem);
	// int id = fork();
	int id = 0;
	int array[5];
	while (i < n && (id = fork()))
	{
		array[i] = id;
		i++;
		usleep(1);
	}
	if (!id)
	{
		if (!sem_wait(sem) && !sem_wait(sem))
		{
		printf("%d\n", getpid());
		printf("%d\n", getpid());
		// int b = sem_getvalue(sem, )
		printf("a = %d\n", getpid());
		sleep(10);
		sem_post(sem);
		sem_post(sem);
		}
			// i = -1;
		// while(++i < 2)
		// 	{
		// 		sem_wait(sem);
		// 		printf("%d\n", getpid());
		// 	}
		// sem_wait(sem);
		// printf("%d\n", getpid());
		// sem_wait(sem);
		// printf("%d\n", getpid());
		// // int b = sem_getvalue(sem, )
		// printf("a = %d\n", getpid());
		// sleep(10);
		// sem_post(sem);
		// sem_post(sem);
	}

	// int id = fork();
	printf("END %d: %d\n", getpid(), getppid());
	if (id)
	{
		for (int j = 0; j < 5; j++)
			printf("%d ", array[j]);
		printf("\n");
	}
	sem_unlink("sem");
	sem_close(sem);
	pause();
	return (0);
}
