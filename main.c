#include "philosophers.h"

t_info *info_init(int argc, char *argv[])
{
	t_info *info;
	
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
	{
		//handle exit
	}
	info->philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	return (info);
}

t_data	*data_init(int argc, char *argv[], t_data *data)
{
	data->info = info_init(argc, argv);
	(data->counter) = 0;
	if (pthread_mutex_init(&(data->mutex), NULL) != 0)
	{
		//handle exit
	}
	data->threads = (pthread_t *)malloc((sizeof(pthread_t) * data->info->philos));
	return (data);
}

void	print_data(t_data *data)
{
	printf("philos := [%d]\n", data->info->philos);
	printf("time_die := [%d]\n", data->info->time_die);
	printf("time_eat := [%d]\n", data->info->time_eat);
	printf("time_sleep := [%d]\n", data->info->time_sleep);
	printf("max_eat := [%d]\n", data->info->max_eat);
}

void	print_table(t_table *table, t_data data)
{
	for (int i = 0; i < 20; i++)//data.info->philos * 2; i++)
	{
		printf("Content id := [%d]\n", table->content_id);
		if (table->content_id == 0)
			printf("Philo id := [%d]\n", ((t_philo *)table->content)->id);
		else
			printf("Fork\n");
		printf("\n");
		table = table->right;
	}
}

void	*thread_start(void *arg)
{

	t_data *data;

	data = (t_data *)arg;
	int thread_id;

	thread_id = data->thread_id;
	printf("Thread start := [%d]\n", thread_id);
	while (data->counter < COUNTER_MAX)
	{
		pthread_mutex_lock(&(((t_fork *)(data->table->left->content))->mutex));
		printf("Thread [%d] has locked fork [%d]\n", thread_id, (((t_fork *)(data->table->left->content))->id));
		pthread_mutex_lock(&(((t_fork *)(data->table->right->content))->mutex));
		printf("Thread [%d] has locked fork [%d]\n", thread_id, (((t_fork *)(data->table->right->content))->id));
		usleep(1000000);
		printf("Thread [%d] will unlock fork [%d]\n", thread_id, (((t_fork *)(data->table->left->content))->id));
		pthread_mutex_unlock(&(((t_fork *)(data->table->left->content))->mutex));
		printf("Thread [%d] will unlock fork [%d]\n", thread_id, (((t_fork *)(data->table->left->content))->id));
		pthread_mutex_unlock(&(((t_fork *)(data->table->right->content))->mutex));
		if (data->counter > COUNTER_MAX)
			break;
		usleep(1000);
	}

	return (NULL);
}

/*
void	*thread_start(void *arg)
{

	t_data *data;

	data = (t_data *)arg;
	int thread_id;

	printf("counter := [%d]\n", data->counter);
	thread_id = data->thread_id;
	printf("Thread start := [%d]\n", thread_id);
	while (data->counter < COUNTER_MAX)
	{
		pthread_mutex_lock(&(data->mutex));
		printf("Thread [%d] has locked mutex\n", thread_id);
		if (data->counter < COUNTER_MAX)
			printf("Thread [%d] has incremented counter from [%d] to [%d]\n", thread_id, (data->counter++), data->counter);
		else
			printf("Counter is already high enough\n");
		usleep(1000000);
		printf("Thread [%d] will now unlock mutex\n", thread_id);
		pthread_mutex_unlock(&(data->mutex));
		usleep(100000);
		if (data->counter > COUNTER_MAX)
			break;
	}

	return (NULL);
}*/

void	bt(t_data data)
{
	t_philo *philo;

	for (int i = 0; i < data.info->philos; i++)//create all threads
	{
		data.thread_id = i;
		philo = data.table->content;
		printf("Starting philo [%d]\n", philo->id);
		if (pthread_create(&(philo->thread), NULL, thread_start, &data) != 0)
		{
			//error handling
		}
		usleep(1000);
	}
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
