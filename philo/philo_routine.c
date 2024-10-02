/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:19:58 by akajjou           #+#    #+#             */
/*   Updated: 2024/10/02 02:13:58 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(FIRST_FORK, philo);
	mutex_handler(&philo->last_fork->fork, LOCK);
	write_status(LAST_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_tm, get_time(MILLISEC));
	philo->meal_count++;
	write_status(EAT, philo);
	sleep_philo(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meal > 0
		&& philo->meal_count == philo->table->max_meal)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->last_fork->fork, UNLOCK);
}

void	philo_sleep(t_philo *philo)
{
	write_status(SLEEP, philo);
	sleep_philo(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo, bool sync)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!sync)
		write_status(THINK, philo);
	if (philo->table->num_philo % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	sleep_philo(t_think * 0.42, philo->table);
}

void	sync_them(t_philo *philo)
{
	if (philo->table->num_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			sleep_philo(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			philo_think(philo, true);
	}
}

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_tm, get_time(MILLISEC));
	for_monitor(philo->table);
	sync_them(philo);
	while (simu_end(philo->table) == false)
	{
		if (philo->full)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo, false);
	}
	return (NULL);
}
