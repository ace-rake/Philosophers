/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:28 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/17 10:11:07 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_philo	*create_philosopher(t_info *info, int id)
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->thread = (pthread_t *)malloc(sizeof(pthread_t) * 1);
	if (!philo->thread)
	{
		free(philo);
		return (NULL);
	}
	philo->id = id / 2;
	philo->info = info;
	philo->times_eaten = 0;
	return (philo);
}

t_fork	*create_fork(int id)
{
	t_fork		*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->id = id / 2;
	fork->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!fork->mutex)
	{
		free(fork);
		return (NULL);
	}
	if (pthread_mutex_init((fork->mutex), NULL) != 0)
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

t_table	*table_con(t_info *info, int id)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->content_id = id / 2;
	if (id % 2 == 0)
		table->content = create_philosopher(info, id);
	else
		table->content = create_fork(id);
	if (table->content == NULL)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

t_table	*create_table(t_data data)
{
	t_table	*table;
	t_table	*start;
	int		iter;

	iter = 0;
	table = table_con(data.info, iter % 2);
	table->spot = 1;
	if (table == NULL)
		return (NULL);
	start = table;
	while (++iter < data.info->philos * 2)
	{
		table->right = table_con(data.info, iter);
		if (table->right == NULL)
			exit_handler(&data);
		table->right->left = table;
		table = table->right;
		table->spot = iter + 1;
	}
	start->left = table;
	table->right = start;
	return (start);
}
