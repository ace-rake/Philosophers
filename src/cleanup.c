/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:47:31 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 13:36:54 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	free_fork(t_fork *fork)
{
	if (pthread_mutex_destroy(fork->mutex) != 0)
	{
		free(fork);
		return (1);
	}
	free(fork->mutex);
	free(fork);
	return (0);
}

void	free_philo(t_philo *philo)
{
	if (philo)
	{
		if (philo->thread)
			free(philo->thread);
		free(philo);
	}
}

void	free_info(t_info *info)
{
	free(info->nu_of_philo_done);
	free(info);
}

int	free_table(t_table *table, int philos)
{
	int		iter;
	t_table	*tmp;

	iter = 0;
	while (iter < philos * 2)
	{
		if (iter % 2 == 0)
			free_philo((t_philo *)table->content);
		else
			free_fork((t_fork *)table->content);
		iter++;
		tmp = table->right;
		free(table);
		table = tmp;
	}
	return (0);
}

int	cleanup(t_data *data)
{
	free(data->start);
	free(data->end);
	free(data->write);
	free(data->checker);
	free_table(data->table, data->info->philos);
	free_info(data->info);
	return (0);
}
