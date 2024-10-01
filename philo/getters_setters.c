/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:46 by akajjou           #+#    #+#             */
/*   Updated: 2024/09/28 17:48:06 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_bool(t_mutex *mutex, bool *dest, bool value)
{
    mutex_handler(mutex, LOCK);
    *dest = value;
    mutex_handler(mutex, UNLOCK);
}

bool    get_bool(t_mutex *mutex, bool *src)
{
    bool value;

    mutex_handler(mutex, LOCK);
    value = *src;
    mutex_handler(mutex, UNLOCK);
    return (value);
}

long    get_long(t_mutex *mutex, long *value)
{
    long ret;

    mutex_handler(mutex, LOCK);
    ret = *value;
    mutex_handler(mutex, UNLOCK);
    return (ret);
}

void   set_long(t_mutex *mutex, long *dest, long value)
{
    mutex_handler(mutex, LOCK);
    *dest = value;
    mutex_handler(mutex, UNLOCK);
}

bool    simu_end(t_table *table)
{
    bool ret;

    ret = get_bool(&table->avoid_race, &table->end_sm);
    return (ret);
}