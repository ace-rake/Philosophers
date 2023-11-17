/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:17:25 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/17 10:02:13 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_info	*info_init(int argc, char *argv[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->nu_of_philo_done = (int *)malloc(sizeof(int) * 1);
	if (!info->nu_of_philo_done)
	{
		free(info);
		return (NULL);
	}
	*info->nu_of_philo_done = 0;
	info->philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	else
		info->max_eat = 2147483647;
	return (info);
}

t_data	*data_init(int argc, char *argv[], t_data *data)
{
	data->end = (int *)malloc(sizeof(int) * 1);
	data->start = (int *)malloc(sizeof(int) * 1);
	*data->end = 0;
	*data->start = 0;
	data->info = info_init(argc, argv);
	if (!data->info)
		exit_handler(data);
	data->checker = (pthread_t *)malloc(sizeof(pthread_t) * 1);
	data->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!data->checker || !data->write)
		exit_handler(data);
	if (pthread_mutex_init(data->write, NULL))
		exit_handler(data);
	data->table = create_table(*data);
	return (data);
}
