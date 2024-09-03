/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:31 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/02 02:44:55 by akajjou          ###   ########.fr       */
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

bool	pilosophers_start(int ac, char **av, t_table table)
{
	printf("Number of philosophers: %d\n", table.num_philo);
	printf("Time to die: %d\n", table.time_to_die);
	printf("Time to eat: %d\n", table.time_to_eat);
	printf("Time to sleep: %d\n", table.time_to_sleep);
	if (ac == 6)
		printf("Number of times each philosopher must eat: %d\n", table.num_eat);
	return (true);
}

bool	table_creation(int ac, char **av, t_table *table)
{
	int i;

	i = 1;
	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (printf("Error: Table creation failed\n"),false);
	table->num_philo = ft_atoi(av[0]);
	table->time_to_die = ft_atoi(av[1]);
	table->time_to_eat = ft_atoi(av[2]);
	table->time_to_sleep = ft_atoi(av[3]);
	if (ac == 6)
		table->num_eat = ft_atoi(av[4]);
	else
		table->num_eat = -1;
	return (true);
}

int		main(int ac, char **av)
{
	t_table *table;

    if (input_parsing(ac, av) == false)
        return (1);
	if (table_creation(ac, av, table) == false)
		return (1);
	if (pilosophers_start(ac, av, table) == false)
		return (1);
	return (0);
}