/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:31 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/24 17:25:17 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	input_parsing(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"),false);
	if (ft_atoi(av[i]) < 1)
		return (printf("Error: Number of philosophers must be greater than 0\n"),false);
	while (av[i])
	{
		if (ft_isdigit(av[i]) == false)
			return (printf("Error: Argument %s is not valide\n", av[i]),false);
	i++;
	}
	return (true);
}


void	sync_threads(t_philo *philos, int philo_nbr , t_table *table)
{
	int i;

	i = 0;
	// while (i < philo_nbr)
	// {
	// 	thread_handler(&philos[i].thread_id, NULL, NULL, JOIN);
	// 	i++;
	// }
	table->start_sm = get_time(MILLISEC);
	printf("Simulation started at %ld\n", table->start_sm);
	
}

// void philo_routine(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	while (philo->table->end_sm == false)
// 	{
// 		philo_thinking(philo);
// 		philo_eating(philo);
// 		philo_sleeping(philo);
// 	}
// }

void	*philo_work(void *arg)
{
	
}

bool	pilosophers_start(t_table *table)
{
	int philo_nbr;
	int i;
	pthread_t *threads;

	philo_nbr = table->num_philo;
	i = 0;
	while (i < philo_nbr)
	{
		thread_handler(&table->philos[i].thread_id, philo_work, &table->philos[i], CREAT);
		i++;
	}
	// sync_threads(table->philos, philo_nbr, table);
	
}

bool	data_init(int ac, char **av, t_table **table)
{
	if (table_init(ac, av, table) == false)
		return (false);
	if (philo_init(*table) == false)
		return (false);
	return (true);
}

int		main(int ac, char **av)
{
	t_table *table;
	
    if (input_parsing(ac, av) == false)
        return (1);
	if (data_init(ac, av, &table) == false)
		return (1);
	if (pilosophers_start(table) == false)
		return (1);
	return (0);
}