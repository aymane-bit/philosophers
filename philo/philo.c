/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:31 by akajjou           #+#    #+#             */
/*   Updated: 2024/10/02 02:35:26 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_monitor(t_mutex *mutex, long *all_philo_sync, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handler(mutex, LOCK);
	if (*all_philo_sync == philo_nbr)
		ret = true;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	*monitor_fct(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!start_monitor(&table->avoid_race, &table->all_philo_sync,
			table->num_philo))
		;
	while (!simu_end(table))
	{
		i = 0;
		while (i < table->num_philo && !simu_end(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->avoid_race, &table->end_sm, true);
				write_status(DIE, table->philos + i);
			}
		}
		i++;
	}
	return (NULL);
}

bool	pilosophers_start(t_table *table)
{
	int			philo_nbr;
	int			i;
	pthread_t	*threads;

	philo_nbr = table->num_philo;
	if (table->max_meal == 0)
		return (true);
	if (philo_nbr == 1)
		solo_philo(table);
	i = 0;
	while (i < philo_nbr)
	{
		thread_handler(&table->philos[i].thread_id, philo_work,
			&table->philos[i], CREAT);
		i++;
	}
	thread_handler(&table->monitor, monitor_fct, table, CREAT);
	table->start_sm = get_time(MILLISEC);
	set_bool(&table->avoid_race, &table->all_thread_sync, true);
	sync_threads(table->philos, philo_nbr, table);
	set_bool(&table->write_mutex, &table->end_sm, true);
	return (true);
}

bool	data_init(int ac, char **av, t_table **table)
{
	if (table_init(ac, av, table) == false)
		return (false);
	if (philo_init(*table) == false)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (input_parsing(ac, av) == false)
		return (1);
	if (data_init(ac, av, &table) == false)
		return (1);
	if (pilosophers_start(table) == false)
		return (1);
	garbage_cleaner(table);
	return (0);
}
