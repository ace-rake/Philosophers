/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:29:17 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/05 15:36:38 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_if_dead(t_time current_time, t_data data, t_table *spot)
{
	t_philo *philo;

	philo = (t_philo *)spot->content;
	if (time_diff(philo->last_eat, current_time) > data.info->time_die)
	{
		printf("%ld %d has died\n", time_diff(data.start_time, current_time), philo->id);
		return (1);
	}
	return (0);
}

int	wait(int time_to_wait, t_data data, t_table *table)
{
	t_time	start_time;
	int	current_diff;
	t_time	current_time;

	current_diff = 0;
	get_time(&start_time);
	while (current_diff < time_to_wait && *(data.end) == 0)
	{
		get_time(&current_time);
		current_diff = (int)time_diff(start_time, current_time);
		if (check_if_dead(current_time, data, table) == 1)
			*(data.end) = 1;
		usleep(10);
	}
	if (*data.end == 0)
		return (0);
	return (1);
}

long	time_diff(t_time start_time, t_time now)
{
	long	usec_diff;
	long	sec_diff;
	long	result;

	sec_diff = now.sec - start_time.sec;
	usec_diff = now.usec - start_time.usec;
	result = sec_diff * 1000 + usec_diff / 1000;

	return (result);
}

int	get_time(t_time *start_time)
{
	struct timeval time;
	int	return_value;

	return_value = gettimeofday(&time, NULL);
	start_time->sec = time.tv_sec;
	start_time->usec = time.tv_usec;
	return (return_value);
}
