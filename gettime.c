#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	struct timeval *time = NULL;
	int 	result;

	time = (struct timeval *)malloc(sizeof(struct timeval));	
	for (int i = 0; 1; i++)
	{
		result = gettimeofday(time, NULL);
		printf("time sec := [%ld] time usec := [%ld]\n",time->tv_sec, time->tv_usec);
	}
}
