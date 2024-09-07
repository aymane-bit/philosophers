/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:31 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/07 12:24:29 by akajjou          ###   ########.fr       */
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

bool	pilosophers_start(int ac, char **av, t_table *table)
{
	printf("num_philo: %d\n", table->num_philo);
	printf("time_to_die: %d\n", table->time_to_die);
	printf("time_to_eat: %d\n", table->time_to_eat);
	printf("time_to_sleep: %d\n", table->time_to_sleep);
	printf("max_meal: %d\n", table->max_meal);
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

int		main(int ac, char **av)
{
	t_table *table;
	
    if (input_parsing(ac, av) == false)
        return (1);
	if (data_init(ac, av, &table) == false)
		return (1);
	if (pilosophers_start(ac, av, table) == false)
		return (1);
	return (0);
}