/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:58:43 by vdenisse          #+#    #+#             */
/*   Updated: 2023/11/02 09:35:47 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

//fuck writing struct timeval
typedef struct s_time
{
	long			sec;
	long			usec;
}					t_time;

typedef struct s_info
{
	int				philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_eat;
	int				*nu_of_philo_done;
}					t_info;

typedef struct s_table
{
	int				spot;
	struct s_table	*left;
	struct s_table	*right;
	int				content_id;
	void			*content;
}					t_table;

# define PRE_START 0
# define DEAD 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define FORK 5

typedef struct s_philosopher
{
	int				times_eaten;
	int				id;
	t_time			last_eat;
	t_info			*info;
	pthread_t		*thread;
}					t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	*mutex;
}					t_fork;

typedef struct s_lock
{
	pthread_mutex_t	mutex;
}					t_lock;

typedef struct s_data
{
	int				*start;
	int				*end;
	t_time			start_time;
	t_table			*table;
	t_info			*info;
	pthread_mutex_t	*write;
	pthread_t		*checker;
}					t_data;

//exit_handler.c
void				exit_handler(t_data *data);

//main.c
int					wait_lock(t_data data);

//checker.c
void				*checker_loop(void *arg);

//philo_behaviour.c
void				*thread_start(void *arg);

//create_table.c
t_table				*create_table(t_data data);

//init.c
t_data				*data_init(int argc, char *argv[], t_data *data);
t_info				*info_init(int argc, char *argv[]);

//printing.c
void				print_data(t_data *data);
void				print_table(t_table *table, t_data data);

//gettime.c
int					get_time(t_time *time);
long				time_diff(t_time start_time, t_time now);
int					check_if_dead(t_data data, t_table *spot);

//cleanup.c
int					cleanup(t_data *data);

//ft_atoi.c
int					ft_atoi(const char *nptr);

//printing.c
void				ft_print_status(int philo_num, t_data *data, int msg);
#endif
