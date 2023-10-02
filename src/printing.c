/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:16:23 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/02 13:17:10 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
			printf("Fork id := [%d]\n", ((t_fork *)table->content)->id);;
		printf("\n");
		table = table->right;
	}
}
