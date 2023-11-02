/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:54:21 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 11:18:09 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_lock(t_data data)
{
	while (*data.start != 1)
		usleep(1);
	return (0);
}

void	philosophers(t_data data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data.info->philos)
	{
		philo = data.table->content;
		if (pthread_create(philo->thread, NULL, thread_start, &data) != 0)
			exit_handler(&data);
		usleep(5000);
		data.table = data.table->right->right;
	}
	pthread_create(data.checker, NULL, checker_loop, &data);
	get_time(&data.start_time);
	*data.start = 1;
	while(*data.end != 1)
		usleep(1);
	pthread_join(*data.checker, NULL);
	i = -1;
	while (++i < data.info->philos)
	{
		philo = data.table->content;
		if (pthread_detach(*philo->thread) != 0)
			exit_handler(&data);
		data.table = data.table->right->right;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_table	*table;

	data_init(argc, argv, &data);
	table = create_table(data);
	data.table = table;
	philosophers(data);
	cleanup(&data);
	return (0);
}

/*
void	*threads(void *arg)
{
	printf("thread_created\n");
	pthread_mutex_t *mutex  = ((pthread_mutex_t *)arg);
	pthread_mutex_unlock(mutex);
	printf("after lock\n");
	while (1)
		usleep(1);
	return (NULL);
}

void	*thread(void *arg)
{
	printf("thread_created\n");
	pthread_mutex_t *mutex  = ((pthread_mutex_t *)arg);
	pthread_mutex_lock(mutex);
	printf("after lock\n");
	while (1)
		usleep(1);
	return (NULL);
}

int	main(int argc, char *argv[])
{

	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_t *mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_unlock(mutex);
	pthread_create(&thread1, NULL, thread, mutex);
	usleep(1000000);
	pthread_create(&thread2, NULL, threads, mutex);
	while(1)
		usleep(1);
	(void ) argc;
	(void ) argv;
	(void ) thread1;
	(void ) thread2;

	return (0);
}
*/
