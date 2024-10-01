/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:16:25 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/30 17:46:01 by akajjou          ###   ########.fr       */
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
    (*table)->all_philo_sync = 0;
    (*table)->all_thread_sync = false;
    mutex_handler(&(*table)->avoid_race, INIT);
    mutex_handler(&(*table)->write_mutex, INIT);
    (*table)->end_sm = false;
    if (ac == 6)
        (*table)->max_meal = ft_atoi(av[5]);
    else
        (*table)->max_meal = -1;
    return (true);
}

void    forks_assigner(t_philo *philo, t_fork *forks, int index)
{
    int philo_nbr;

    philo_nbr = philo->table->num_philo;
    
    philo->first_fork = &forks[(index + 1) % philo_nbr];
    philo->last_fork = &forks[index];
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[index];
        philo->last_fork = &forks[(index + 1) % philo_nbr];
    }

}

void    philo_init_helper(t_table *table)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < table->num_philo)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->meal_count = 0;
        philo->full = false;
        philo->table = table;
        mutex_handler(&philo->philo_mutex, INIT);
        forks_assigner(philo, table->forks, i);
    i++;
    }
}

bool	philo_init(t_table *table)
{
    int i;

    i = 0;
    table->philos = malloc(sizeof(t_philo) * table->num_philo);
    table->forks = malloc(sizeof(t_fork) * table->num_philo);
    while (i < table->num_philo)
    {
        mutex_handler(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
        i++;
    }
    philo_init_helper(table);
    return (true);
}
