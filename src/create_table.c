/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:28 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/02 13:14:11 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_philo	*create_philosopher(t_info *info)
{
	t_philo	*philo;
	static int	id = 0;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id++;
	philo->info = info;
	philo->state = PRE_START;
	philo->last_update = NULL;
	return (philo);
}

t_fork	*create_fork(void)
{
	t_fork *fork;
	static int id = 0;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->id =id++;
	if (pthread_mutex_init(&(fork->mutex), NULL) != 0)
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

t_table	*table_con(t_info *info, int id)
{
	t_table *table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->content_id = id;
	if (id == 0)
		table->content = create_philosopher(info);
	else
		table->content = create_fork();
	if (table->content == NULL)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

t_table	*create_table(t_data data)
{
	t_table *table;
	t_table	*start;
	int	iter;

	iter = 0;
	table = table_con(data.info, iter % 2);
	table->spot = 0;
	if (table == NULL)
		return (NULL);
	start = table;
	while (++iter < data.info->philos * 2)
	{
		table->right = table_con(data.info, iter % 2);
		if (table->right == NULL)
		{
			//free created table and handle exit
		}
		table->right->left = table;
		table = table->right;
		table->spot = iter;
	}
	start->left = table;
	table->right = start;

	return (start);
}
