/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:34:38 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 09:41:52 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	patience(int philos, int thread_id, t_info *info, t_data *data)
{
	ft_print_status(thread_id, data, THINKING);
	if (thread_id % 2 == 0 && philos % 2 == 0)
		usleep(info->time_die / 2);
	else if (thread_id % 3 == 0 && philos % 3 == 0)
	{
		if (thread_id % 2 == 0)
			usleep(info->time_die / 3);
		if (thread_id % 3 == 0)
			usleep((info->time_die * 2) / 3);
	}
}

void	cycle_patience(int philos, int thread_id, t_info *info, t_data *data)
{
	int	times_eaten;
	int	time_wait;

	ft_print_status(thread_id, data, THINKING);
	if (philos % 2 == 0)
		return ;
	times_eaten = ((t_philo *)data->table->content)->times_eaten;
	if (thread_id % 3 == 1)
		time_wait = times_eaten % 3;
	else
		time_wait = times_eaten % 2;
	time_wait *= info->time_die / 4;
	usleep(time_wait);
}

int	take_forks(t_table *table, t_data *data, int thread_id)
{
	if (thread_id % 2 == 0)
		pthread_mutex_lock((((t_fork *)(table->left->content))->mutex));
	else
		pthread_mutex_lock((((t_fork *)(table->right->content))->mutex));
	ft_print_status(thread_id, data, FORK);
	if (thread_id % 2 == 0)
		pthread_mutex_lock((((t_fork *)(table->right->content))->mutex));
	else
		pthread_mutex_lock((((t_fork *)(table->left->content))->mutex));
	ft_print_status(thread_id, data, FORK);
	return (0);
}

int	cycle(t_table *table, t_data *data, int thread_id)
{
	while (*(data->end) == 0
		&& ((t_philo *)table->content)->times_eaten < data->info->max_eat)
	{
		if (take_forks(table, data,thread_id))
			break ;
		((t_philo *)(table->content))->times_eaten++;
		get_time(&((t_philo *)table->content)->last_eat);
		if (*data->end != 1)
			ft_print_status(thread_id, data, EATING);
		usleep(data->info->time_eat);
		pthread_mutex_unlock((((t_fork *)(table->left->content))->mutex));
		pthread_mutex_unlock((((t_fork *)(table->right->content))->mutex));
		if (((t_philo *)table->content)->times_eaten >= data->info->max_eat)
		{
			(*data->info->nu_of_philo_done)++;
			break ;
		}
		if (*data->end != 1)
			ft_print_status(thread_id, data, SLEEPING);
		usleep(data->info->time_sleep);
		if (*data->end != 1)
			cycle_patience(data->info->philos, thread_id, data->info, data);
	}
	return (0);
}

void	*thread_start(void *arg)
{
	t_data	*data;
	t_table	*table;
	int		thread_id;

	data = (t_data *)arg;
	table = data->table;
	thread_id = ((t_philo *)(data->table->content))->id;
	printf("thread : [%d] is now waiting.\n", thread_id);
	wait_lock(*data);
	get_time(&((t_philo *)table->content)->last_eat);
	printf("thread : [%d] is now starting cycle.\n", thread_id);
	patience(data->info->philos, thread_id, data->info, data);
	cycle(table, data, thread_id);
	pthread_mutex_unlock((((t_fork *)(table->left->content))->mutex));
	pthread_mutex_unlock((((t_fork *)(table->right->content))->mutex));
	while (1)
		usleep(1);
	return (NULL);
}
