/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:58:43 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/29 16:31:17 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "src/libft/libft.h"
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define	COUNTER_MAX 10

//fuck writing struct timeval
typedef struct	s_time
{
	long sec;
	long usec;
}				t_time;
int	get_time(t_time *time);

typedef struct s_info
{
	int	philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	max_eat;
} t_info;

typedef struct	s_table
{
	struct s_table	*left;
	struct s_table	*right;
	int		content_id;
	void	*content;
}				t_table;

#define PRE_START 0
#define DEAD 1
#define EATING 2
#define SLEEPING 3
#define THINKING 4

typedef struct	s_philosopher
{
	int	id;
	t_time *last_update;
	t_info	*info;
	int	state;
	pthread_t thread;
}				t_philo;

typedef struct s_fork
{
	int	id;
	pthread_mutex_t mutex;
}				t_fork;

typedef struct s_data
{
	t_table *table;
	pthread_t *threads;
	int	thread_id;
	t_info	*info;
	pthread_mutex_t mutex;
	int	counter;
}				t_data;

//creating simple mutex
typedef struct	s_data_mutex
{
	int	current_thread_id;
	int	counter;
	pthread_mutex_t mutex;
}				t_data_mutex;
t_table	*create_table(t_data data);
#endif
