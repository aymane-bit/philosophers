/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:28:45 by akajjou           #+#    #+#             */
/*   Updated: 2024/10/02 02:36:43 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philos(t_table *table)
{
	while (!get_bool(&table->avoid_race, &table->all_thread_sync))
		;
}

void	sync_threads(t_philo *philos, int philo_nbr, t_table *table)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		thread_handler(&philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

void	for_monitor(t_table *table)
{
	mutex_handler(&table->avoid_race, LOCK);
	(table->all_philo_sync)++;
	mutex_handler(&table->avoid_race, UNLOCK);
}
void 	lone_philo(t_table *table)
{
	thread_handler();
	
}
