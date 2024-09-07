/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:16:25 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/07 12:26:21 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	table_init(int ac, char **av, t_table **table)
{
    *table = malloc(sizeof(t_table));
    if (table == NULL)
        return (printf("Error: Table creation failed\n"),false);
    (*table)->num_philo = ft_atoi(av[1]);
    (*table)->time_to_die = ft_atoi(av[2]) * 1e3;
    (*table)->time_to_eat = ft_atoi(av[3]) * 1e3;
    (*table)->time_to_sleep = ft_atoi(av[4]) * 1e3;
    (*table)->end_sm = false;
    if (ac == 6)
        (*table)->max_meal = ft_atoi(av[5]);
    else
        (*table)->max_meal = -1;
    return (true);
}

bool	philo_init(t_table *table)
{
    table->philos = malloc(sizeof(t_philo) * table->num_philo);
    table->forks = malloc(sizeof(t_fork) * table->num_philo);
}
