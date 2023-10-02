/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:17:25 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/02 13:18:08 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_info *info_init(int argc, char *argv[])
{
	t_info *info;
	
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
	{
		//handle exit
	}
	info->philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	return (info);
}

t_data	*data_init(int argc, char *argv[], t_data *data)
{
	data->info = info_init(argc, argv);
	data->threads = (pthread_t *)malloc((sizeof(pthread_t) * data->info->philos));
	return (data);
}

