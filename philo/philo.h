/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:00:55 by akajjou           #+#    #+#             */
/*   Updated: 2024/10/02 02:29:11 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

/*for colors*/
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"

typedef enum e_time
{
	MILLISEC,
	MICROSEC,
	SEC,
}						t_time;

typedef enum e_philo_stat
{
	EAT,
	SLEEP,
	THINK,
	DIE,
	FIRST_FORK,
	LAST_FORK,
}						t_philo_stat;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	DESTROY,
	JOIN,
	INIT,
	DETACH,
	CREAT,
}						t_code;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					meal_count;
	bool				full;
	long				last_meal_tm;
	t_mutex				philo_mutex;
	t_fork				*first_fork;
	t_fork				*last_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_meal;
	long				start_sm;
	long				all_philo_sync;
	bool				all_thread_sync;
	bool				end_sm;
	pthread_t			monitor;
	t_mutex				write_mutex;
	t_mutex				avoid_race;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

bool					ft_isdigit(char *str);
long					ft_atoi(const char *str);

/*data intialization*/
bool					table_init(int ac, char **av, t_table **table);
bool					philo_init(t_table *table);
bool					input_parsing(int ac, char **av);

/*thread_fct*/
void					mutex_handler(t_mutex *mutex, t_code code);
void					thread_handler(pthread_t *thread,
							void *(*start)(void *), void *arg, t_code code);
void					wait_philos(t_table *table);
void					sync_threads(t_philo *philos, int philo_nbr,
							t_table *table);
bool					simu_end(t_table *table);
void					*philo_work(void *arg);
void					write_status(t_philo_stat status, t_philo *philo);
bool					philo_died(t_philo *philo);

/*time_fct*/
long					get_time(t_time time);
void					sleep_philo(long usec, t_table *table);

/*getter_setters_fct*/
void					set_bool(t_mutex *mutex, bool *dest, bool value);
bool					get_bool(t_mutex *mutex, bool *src);
long					get_long(t_mutex *mutex, long *value);
void					set_long(t_mutex *mutex, long *dest, long value);
long					get_time(t_time time);
void					for_monitor(t_table *table);

/*cleaner*/
void					garbage_cleaner(t_table *table);

#endif