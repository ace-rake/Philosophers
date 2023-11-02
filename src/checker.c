/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:36:03 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 11:14:04 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*checker_loop(void *arg)
{
	t_data	*data;
	t_table	*table;

	data = (t_data *)arg;
	table = data->table;
	wait_lock(*data);
	usleep(data->info->time_die * 1000);
	while (*data->end != 1)
	{
		if (check_if_dead(*data, table))
			*data->end = 1;
		usleep(1000);
		if (*data->info->nu_of_philo_done >= data->info->philos)
			*data->end = 1;
		table = table->right->right;
	}
	return (NULL);
}
