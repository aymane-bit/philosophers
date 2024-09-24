/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 00:49:53 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/22 18:30:13 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}
/*pthread fct*/
// init
// destroy
// lock 
//unlcok

void	thread_handler(pthread_t *thread, void *(*start)(void *)
						, void *arg, t_code code)
{
	if (code == CREAT)
		pthread_create(thread, NULL, start, arg);
	else if (code == JOIN)
		pthread_join(*thread, NULL);
	else if (code == DETACH)
		pthread_detach(*thread);
}

void	mutex_handler(t_mutex *mutex, t_code code)
{
	if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
}

long    get_time(t_time time)
{
    struct timeval  tv;
    long            time_in_mill;

    gettimeofday(&tv, NULL);
    time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    if (time == MILLISEC)
        return (time_in_mill);
    else if (time == USEC)
        return (time_in_mill * 1000);
    else if (time == SEC)
        return (time_in_mill / 1000);
    return (0);
}

