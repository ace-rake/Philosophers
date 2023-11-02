/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:16:23 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 09:49:59 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_print_status(int philo_num, t_data *data, int msg)
{
	t_time	now;
	long	diff;

	while (pthread_mutex_lock(data->write) != 0)
		usleep(1);
	get_time(&now);
	diff = time_diff(data->start_time, now);
	philo_num++;
	if (msg == DEAD)
	{
		printf("%ld %d died\n", diff, philo_num);
		return ;
	}
	if (msg == EATING)
		printf("%ld %d is eating\n", diff, philo_num);
	if (msg == SLEEPING)
		printf("%ld %d is sleeping\n", diff, philo_num);
	if (msg == THINKING)
		printf("%ld %d is thinking\n", diff, philo_num);
	if (msg == FORK)
		printf("%ld %d has taken a fork\n", diff, philo_num);
	pthread_mutex_unlock(data->write);
}
/*
void	print_data(t_data *data)
{
	printf("philos := [%d]\n", data->info->philos);
	printf("time_die := [%d]\n", data->info->time_die);
	printf("time_eat := [%d]\n", data->info->time_eat);
	printf("time_sleep := [%d]\n", data->info->time_sleep);
	printf("max_eat := [%d]\n\n", data->info->max_eat);
}

void	print_table(t_table *table, t_data data)
{
	for (int i = 0; i < data.info->philos * 2; i++)
	{
		printf("Table spot := [%d]\n", table->spot);
		printf("Content id := [%d]\n", table->content_id);
		if (table->content_id == 0)
			printf("Philo id := [%d]\n", ((t_philo *)table->content)->id);
		else
			printf("Fork id := [%d]\n", ((t_fork *)table->content)->id);
		printf("\n");
		table = table->right;
	}
}
*/
