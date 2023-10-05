#include "philosophers.h"

int	wait_lock(t_data data)
{
	while (*data.start != 1)
		usleep(1);
	return (0);
}

int	take_forks(t_table *table, t_data *data, t_time *time, int thread_id)
{
	if (thread_id % 2 == 0)
		pthread_mutex_lock(&(((t_fork *)(table->left->content))->mutex));
	else
		pthread_mutex_lock(&(((t_fork *)(table->right->content))->mutex));
	get_time(time);
	printf("%ld %d has taken a fork\n", time_diff(data->start_time, *time), thread_id);
	if (thread_id %2 == 0)
		pthread_mutex_lock(&(((t_fork *)(table->right->content))->mutex));
	else
		pthread_mutex_lock(&(((t_fork *)(table->left->content))->mutex));
	get_time(time);
	printf("%ld %d has taken a fork\n", time_diff(data->start_time, *time), thread_id);
	return (0);	
}

int	cycle(t_table *table, t_data *data, t_time *time, int thread_id)
{
	while (*(data->end) == 0)//make this so it checks if this philo has eaten enough times and also for end
	{
		if (take_forks(table, data, time, thread_id))
			break;
		get_time(time);
		printf("%ld %d is eating\n",time_diff(data->start_time, *time), thread_id);
		get_time(&((t_philo *)table->content)->last_eat);
		if (wait(data->info->time_eat, *data, table) == 1)
			break;
		pthread_mutex_unlock(&(((t_fork *)(table->left->content))->mutex));
		pthread_mutex_unlock(&(((t_fork *)(table->right->content))->mutex));
		get_time(time);
		printf("%ld %d is sleeping\n", time_diff(data->start_time, *time), thread_id);
		if (wait(data->info->time_sleep, *data, table) == 1)
			break;
		get_time(time);
	}
	return (0);
}

void	*thread_start(void *arg)
{
	t_data *data;
	t_table *table;
	t_time time;
	int thread_id;

	data = (t_data *)arg;
	table = data->table;
	thread_id = ((t_philo *)(data->table->content))->id;
	wait_lock(*data);
	if (thread_id % 2 == 0)
		usleep(data->info->time_eat);
	cycle(table, data, &time, thread_id);
	pthread_mutex_unlock(&(((t_fork *)(table->left->content))->mutex));
	pthread_mutex_unlock(&(((t_fork *)(table->right->content))->mutex));
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
