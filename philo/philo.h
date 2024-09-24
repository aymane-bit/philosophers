/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:00:55 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/22 18:29:38 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

/*for colors*/
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

typedef enum e_time
{
	MILLISEC,
	USEC,
	SEC,
}			t_time;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	DESTROY,
	JOIN,
	INIT,
	DETACH,
	CREAT,
}			t_code;

typedef struct s_table  t_table;
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	t_mutex		fork;
	int 				fork_id;
}					t_fork;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	bool		full;
	int 		last_meal_tm;
	t_fork		*first_fork;
	t_fork		*last_fork;
	pthread_t	thread_id;
	t_table		*table;
}					t_philo;


typedef struct s_table
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meal;
	long		start_sm;
	bool		end_sm;
	t_fork		*forks;
	t_philo		*philos;
}					t_table;


bool	ft_isdigit(char *str);
int		ft_atoi(const char *str);


/*data intialization*/
bool	table_init(int ac, char **av, t_table **table);
bool	philo_init(t_table *table);

/*thread_fct*/
void	mutex_handler(t_mutex *mutex, t_code code);
void	thread_handler(pthread_t *thread, void *(*start)(void *)
						, void *arg, t_code code);

/*time_fct*/
long	get_time(t_time time);



#endif