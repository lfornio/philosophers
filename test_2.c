#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int take_time()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
void my_usleep(int a)
{
	int stop = take_time() + a;
	int time_now = take_time();
	while(time_now < stop)
	{
		usleep(10);
		time_now = take_time();
	}
}

int main()
{
	int a, b, c;
	a = take_time();
	// usleep(200 * 1000);
	my_usleep(200);
	b = take_time();
	// b = take_time() - a;
	c = b - a;
	printf("time = %d\n", c);

	write(1, "Exit\n", 5);
	return (0);
}
