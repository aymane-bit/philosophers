/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:49:09 by akajjou           #+#    #+#             */
/*   Updated: 2024/10/02 02:29:52 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	input_parsing(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"), false);
	if (ft_atoi(av[i]) < 1)
	{
		printf("Error: Number of philosophers must be greater than 0\n");
		return (false);
	}
	while (av[i])
	{
		if (ft_isdigit(av[i]) == false)
			return (printf("Error: Argument %s is not valide\n", av[i]), false);
		i++;
	}
	return (true);
}

void	sleep_philo(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remain;

	start = get_time(MICROSEC);
	while (get_time(MICROSEC) - start < usec)
	{
		if (simu_end(table))
			break ;
		elapsed = get_time(MICROSEC) - start;
		remain = usec - elapsed;
		if (remain == 1e3)
			usleep(remain / 2);
		else
			while (get_time(MICROSEC) - start < usec)
				;
	}
}

void	write_status(t_philo_stat status, t_philo *philo)
{
	mutex_handler(&philo->table->write_mutex, LOCK);
	if ((status == FIRST_FORK || status == LAST_FORK)
		&& !simu_end(philo->table))
		printf(GREEN "%ld %d has taken a fork\n" RESET, get_time(MILLISEC)
			- philo->table->start_sm, philo->id);
	else if (status == EAT && !simu_end(philo->table))
		printf(RED "%ld %d is eating\n" RESET, get_time(MILLISEC)
			- philo->table->start_sm, philo->id);
	else if (status == SLEEP && !simu_end(philo->table))
		printf(MAGENTA "%ld %d is sleeping\n" RESET, get_time(MILLISEC)
			- philo->table->start_sm, philo->id);
	else if (status == THINK && !simu_end(philo->table))
		printf("%ld %d is thinking\n", get_time(MILLISEC)
			- philo->table->start_sm, philo->id);
	else if (status == DIE)
		printf("%ld %d died\n", get_time(MILLISEC) - philo->table->start_sm,
			philo->id);
	mutex_handler(&philo->table->write_mutex, UNLOCK);
}

bool	philo_died(t_philo *philo)
{
	long	time_to_die;
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISEC) - get_long(&philo->philo_mutex,
			&philo->last_meal_tm);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
	{
		return (true);
	}
	return (false);
}

void	garbage_cleaner(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philo)
	{
		philo = table->philos + i;
		mutex_handler(&philo->philo_mutex, DESTROY);
		i++;
	}
	mutex_handler(&table->write_mutex, DESTROY);
	mutex_handler(&table->avoid_race, DESTROY);
	free(table->philos);
	free(table->forks);
	free(table);
}
