#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long long gettimesec()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
void count_time(int a)
{
	long long end = gettimesec() + a;
	long long time_now = gettimesec();
	while(time_now < end)
	{
		usleep(10);
		time_now = gettimesec();
	}
}

int main()
{
	long long a, b;
	int c;
	a = gettimesec();
	// usleep(200 * 1000);
	my_usleep(200);
	b = gettimesec();
	// b = take_time() - a;
	c = (int) (b - a);
	printf("time = %d\n", c);

	write(1, "Exit\n", 5);
	return (0);
}
