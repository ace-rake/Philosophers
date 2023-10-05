#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_time start;
	t_time now;
	long diff = 0;
	start.usec = 0;
	start.sec = 0;
	now.usec = 0;
	now.sec = 0;
	t_data data;
	data_init(argc, argv, &data);
	data.info->time_die = 10000000;
	data.table = create_table(data);
	get_time(&data.start_time);
	data.end = (int *)malloc(sizeof(int));
	*data.end = 0;
	for (int i = 0; diff < 10000; i++)
	{
		wait(1000, data, data.table);
		get_time(&now);
		diff = time_diff(data.start_time, now);
		printf("Diff := [%ld]\n", diff);	
	}
}
