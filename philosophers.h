/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:58:43 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/09 11:30:27 by vdenisse         ###   ########.fr       */
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
	int	spot;
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
	int	times_eaten;
	int	id;
	t_time last_eat;
	t_info	*info;
	int	state;
	pthread_t thread;
}				t_philo;

typedef struct s_fork
{
	int	id;
	pthread_mutex_t mutex;
}				t_fork;

typedef struct s_lock
{
	pthread_mutex_t mutex;	
}	t_lock;

typedef struct s_data
{
	int	*start;
	int	*end;
	t_time start_time;
	t_lock lock;
	t_table *table;
	pthread_t *threads;
	t_info	*info;
}				t_data;

//creating simple mutex
typedef struct	s_data_mutex
{
	int	current_thread_id;
	int	counter;
	pthread_mutex_t mutex;
}				t_data_mutex;

//create_table.c
t_table	*create_table(t_data data);

//init.c
t_data	*data_init(int argc, char *argv[], t_data *data);
t_info *info_init(int argc, char *argv[]);

//printing.c
void	print_data(t_data *data);
void	print_table(t_table *table, t_data data);

//gettime.c
int	get_time(t_time *time);
long	time_diff(t_time start_time, t_time now);
int	wait(int time_to_wait, t_data data, t_table *table);
#endif
