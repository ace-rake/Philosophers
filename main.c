/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:54:21 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 13:52:38 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	wait_lock(t_data data)
{
	while (*data.start != 1)
		usleep(1);
	return (0);
}

void	philosophers(t_data data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data.info->philos)
	{
		philo = data.table->content;
		if (pthread_create(philo->thread, NULL, thread_start, &data) != 0)
			exit_handler(&data);
		usleep(5000);
		data.table = data.table->right->right;
	}
	pthread_create(data.checker, NULL, checker_loop, &data);
	get_time(&data.start_time);
	*data.start = 1;
	pthread_join(*data.checker, NULL);
	i = -1;
	while (++i < data.info->philos)
	{
		philo = data.table->content;
		if (pthread_detach(*philo->thread) != 0)
			exit_handler(&data);
		data.table = data.table->right->right;
	}
}

int	error_check(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i]) != 1)
		{
			printf("error: Non numerical input\n");
			return (1);
		}
		++i;
	}
	if (argc != 5 && argc != 6)
	{
		printf("argument error\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_table	*table;

	if (error_check(argc, argv))
		return (1);
	data_init(argc, argv, &data);
	table = create_table(data);
	data.table = table;
	philosophers(data);
	cleanup(&data);
	return (0);
}
