/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:34:38 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/17 10:47:04 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	take_forks(t_table *t, t_data *data, int thread_id)
{
	if (thread_id % 2 == 0)
	{
		if (pthread_mutex_lock((((t_fork *)(t->left->content))->mutex)) != 0)
			return (1);
	}
	else if (pthread_mutex_lock((((t_fork *)(t->right->content))->mutex)) != 0)
		return (1);
	ft_print_status(thread_id, data, FORK);
	usleep(200);
	if (thread_id % 2 == 0)
	{
		if (pthread_mutex_lock((((t_fork *)(t->right->content))->mutex)) != 0)
			return (1);
	}
	else if (pthread_mutex_lock((((t_fork *)(t->left->content))->mutex)) != 0)
		return (1);
	ft_print_status(thread_id, data, FORK);
	return (0);
}

int	cycle(t_table *table, t_data *data, int thread_id)
{
	while (*(data->end) == 0
		&& ((t_philo *)table->content)->times_eaten < data->info->max_eat)
	{
		if (take_forks(table, data, thread_id))
			break ;
		((t_philo *)(table->content))->times_eaten++;
		get_time(&((t_philo *)table->content)->last_eat);
		if (*data->end != 1)
			ft_print_status(thread_id, data, EATING);
		usleep(data->info->time_eat * 1000);
		if (pthread_mutex_unlock((((t_fork *)(table->left->content))->mutex)))
			break ;
		if (pthread_mutex_unlock((((t_fork *)(table->right->content))->mutex)))
			break ;
		if (((t_philo *)table->content)->times_eaten >= data->info->max_eat)
		{
			(*data->info->nu_of_philo_done)++;
			break ;
		}
		if (*data->end != 1)
			ft_print_status(thread_id, data, SLEEPING);
		usleep(data->info->time_sleep * 1000);
		ft_print_status(thread_id, data, THINKING);
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
	wait_lock(*data);
	get_time(&((t_philo *)table->content)->last_eat);
	ft_print_status(thread_id, data, THINKING);
	if (thread_id % 2 == 0)
		usleep(1000);
	cycle(table, data, thread_id);
	pthread_mutex_unlock((((t_fork *)(table->left->content))->mutex));
	pthread_mutex_unlock((((t_fork *)(table->right->content))->mutex));
	return (NULL);
}
