/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:29:17 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/31 16:18:54 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_if_dead(t_data data, t_table *spot)
{
	t_philo	*philo;
	t_time	current_time;

	philo = (t_philo *)spot->content;
	get_time(&current_time);
/*	printf("\nchecking : [%d]\n", philo->id);
	printf("amount check := [%d] : [%d]\n", philo->times_eaten, data.info->max_eat);
	printf("last eat := [%zu] , [%zu]\n", philo->last_eat.sec, philo->last_eat.usec);
	printf("time check := [%zu] : [%d]\n\n", time_diff(philo->last_eat, current_time), data.info->time_die);
*/	if (philo->times_eaten < data.info->max_eat)
	{
		if (time_diff(philo->last_eat, current_time) > data.info->time_die)
		{
			ft_print_status(((t_philo *)spot->content)->id, &data, DEAD);
			return (1);
		}
	}
	return (0);
}

long	time_diff(t_time start_time, t_time now)
{
	long			usec_diff;
	long			sec_diff;
	long			result;
	pthread_mutex_t	mutex;

	pthread_mutex_lock(&mutex);
	sec_diff = now.sec - start_time.sec;
	usec_diff = now.usec - start_time.usec;
	result = sec_diff * 1000 + usec_diff / 1000;
	pthread_mutex_unlock(&mutex);
	return (result);
}

int	get_time(t_time *start_time)
{
	struct timeval	time;
	int				return_value;

	return_value = gettimeofday(&time, NULL);
	start_time->sec = time.tv_sec;
	start_time->usec = time.tv_usec;
	return (return_value);
}
