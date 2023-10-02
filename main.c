#include "philosophers.h"

void	*thread_start(void *arg)
{
	t_data *data;
	t_table *table;

	data = (t_data *)arg;
	table = data->table;
	int thread_id;

	thread_id = ((t_philo *)(data->table->content))->id;
	printf("Thread start := [%d] and my table spot is [%d]\n", thread_id, data->table->spot);
	while (1)//make this so it checks if this philo has eaten enough times
	{
		pthread_mutex_lock(&(((t_fork *)(table->left->content))->mutex));
		printf("Thread [%d] has locked fork [%d]\n", thread_id, (((t_fork *)(table->left->content))->id));
		pthread_mutex_lock(&(((t_fork *)(table->right->content))->mutex));
		printf("Thread [%d] has locked fork [%d]\n", thread_id, (((t_fork *)(table->right->content))->id));
		usleep(1000000);
		printf("Thread [%d] will unlock fork [%d]\n", thread_id, (((t_fork *)(table->left->content))->id));
		pthread_mutex_unlock(&(((t_fork *)(table->left->content))->mutex));
		printf("Thread [%d] will unlock fork [%d]\n", thread_id, (((t_fork *)(table->right->content))->id));
		pthread_mutex_unlock(&(((t_fork *)(table->right->content))->mutex));
		usleep(100000);
		//create end condition
	}
	return (NULL);
}

void	bt(t_data data)
{
	t_philo *philo;

	for (int i = 0; i < data.info->philos; i++)//create all threads
	{
		philo = data.table->content;
		printf("Starting philo [%d]\n", philo->id);
		if (pthread_create(&(philo->thread), NULL, thread_start, &data) != 0)
		{
			//error handling
		}
		data.table = data.table->right->right;
		usleep(10000);
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

//maybe create a start struct just containing a mutex, lock said mutex in main, have all the threads try to lock and instantly unlock mutex, thath way i can just unlock the mutex in the main as a sort of starting shot

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
