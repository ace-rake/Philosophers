/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:24:35 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/29 10:33:53 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define THREAD_NUM 10
#define COUNT_MAX 20
/*
void	*func(void *arg)
{
	t_data_mutex *data_mutex;
	int	thread_id;

	data_mutex = (t_data_mutex *)arg;
	pthread_mutex_lock(&(data_mutex->mutex));
	thread_id = data_mutex->current_thread_id;
	data_mutex->counter++;
	printf("thread with id := [%d] incremented counter to := [%d]\n", thread_id, data_mutex->counter);
//	usleep(1000000);
	pthread_mutex_unlock(&(data_mutex->mutex));
//	printf("thread with id := [%d] finished\n", thread_id);
	return (NULL);
}
*/
void	*func(void *arg)
{

	t_data_mutex *data;

	data = (t_data_mutex *)arg;
	int thread_id;

	printf("counter := [%d]\n", data->counter);
	thread_id = data->current_thread_id;
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
}
int	main(void)
{
	t_data_mutex data_mutex;
	pthread_t threads[THREAD_NUM];

	data_mutex.counter = 0;
	if (pthread_mutex_init(&(data_mutex.mutex), NULL) != 0)//create mutex
	{
		//error handling
	}

	for (int i = 0; i < THREAD_NUM; i++)//create all threads
	{
		data_mutex.current_thread_id = i;
		printf("starting thread [%d]\n", i);
		if (pthread_create(&threads[i], NULL, func, &data_mutex) != 0)
		{
			//error handling
		}
		usleep(100000);
	}
	for (int i = 0; i < THREAD_NUM; i++)//wait for all pthreads to finnish
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			//error handling
		}
		printf("Thread [%d] has joined\n", i);
	}
	if (pthread_mutex_destroy(&(data_mutex.mutex)) != 0)
	{
		//error handling
	}
	printf("Main thread end\n");
}
