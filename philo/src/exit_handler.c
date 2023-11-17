/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:01:26 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 09:37:24 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	detach_all_threads(t_data *data)
{
	int		iter;
	t_table	*table;
	t_philo	*philo;

	iter = 0;
	table = data->table;
	while (iter < data->info->philos)
	{
		philo = (t_philo *)table->content;
		if (pthread_detach(*philo->thread) != 0)
			exit_handler(data);
		table = table->right->right;
		iter++;
	}
	if (pthread_detach(*data->checker) != 0)
		exit_handler(data);
}

void	exit_handler(t_data *data)
{
	if (data)
	{
		detach_all_threads(data);
		cleanup(data);
	}
	exit(1);
}
