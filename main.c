#include "philosophers.h"

int	wait_lock(t_data data)
{
	while (*data.start != 1)
		usleep(1);
	return (0);
}

void	*thread_start(void *arg)
{
	t_data *data;
	t_table *table;
	t_time time;

	time.usec = 0;
	data = (t_data *)arg;
	table = data->table;
	int thread_id;
	thread_id = ((t_philo *)(data->table->content))->id;
	printf("Thread start := [%d] and my table spot is [%d]\n", thread_id, data->table->spot);
	wait_lock(*data);
	if (thread_id % 2 == 0)
		usleep(100000);
	while (*(data->end) == 0)//make this so it checks if this philo has eaten enough times and also for end
	{
		pthread_mutex_lock(&(((t_fork *)(table->left->content))->mutex));
		get_time(&time);
		printf("%ld %d has taken a fork\n", time_diff(data->start_time, time), thread_id);
		pthread_mutex_lock(&(((t_fork *)(table->right->content))->mutex));
		get_time(&time);
		printf("%ld %d has taken a fork\n", time_diff(data->start_time, time), thread_id);
		printf("%ld %d is eating\n",time_diff(data->start_time, time), thread_id);
		get_time(&((t_philo *)table->content)->last_eat);
		usleep(100000);
//		if (wait(data->info->time_eat, *data, table) == 1)
//			break;
		pthread_mutex_unlock(&(((t_fork *)(table->left->content))->mutex));
		pthread_mutex_unlock(&(((t_fork *)(table->right->content))->mutex));
		get_time(&time);
		printf("%ld %d is sleeping\n", time_diff(data->start_time, time), thread_id);
		usleep(100000);
//		if (wait(data->info->time_sleep, *data, table) == 1)
//			break;
		//create end condition
	}
	return (NULL);
}

void	bt(t_data data)
{
	t_philo *philo;

	pthread_mutex_init(&data.lock.mutex, NULL);
	pthread_mutex_lock(&data.lock.mutex);

	data.end = (int *)malloc(sizeof(int) * 1);
	*data.end = 0;
	data.start =  (int *)malloc(sizeof(int) * 1);
	*data.start = 0;
	for (int i = 0; i < data.info->philos; i++)//create all threads
	{
		philo = data.table->content;
//		printf("Starting philo [%d]\n", philo->id);
		if (pthread_create(&(philo->thread), NULL, thread_start, &data) != 0)
		{
			//error handling
		}
		data.table = data.table->right->right;
		usleep(100000);
	}
	get_time(&data.start_time);
	*data.start = 1;
	pthread_mutex_unlock(&data.lock.mutex);
	for (int i = 0; i < data.info->philos; i++)//wait for all pthreads to finnish
	{
		philo = data.table->content;
		if (pthread_join(philo->thread, NULL) != 0)
		{
			//error handling
		}
		printf("Philo [%d] has joined\n", philo->id);
	}
}

int main(int argc, char *argv[])
{
	t_data data;

	data_init(argc, argv, &data);
	print_data(&data);
	t_table *table = create_table(data);	
	data.table = table;
	print_table(table, data);
	bt(data);
    return 0;
}
