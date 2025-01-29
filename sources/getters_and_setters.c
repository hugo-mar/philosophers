/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:05:48 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/29 12:21:20 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	safe_value;

	pthread_mutex_lock(mutex);
	safe_value = *value;
	pthread_mutex_unlock(mutex);
	return (safe_value);
}

void	set_bool(t_mutex *mutex, bool *value, bool new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	safe_value;

	pthread_mutex_lock(mutex);
	safe_value = *value;
	pthread_mutex_unlock(mutex);
	return (safe_value);
}

void	set_long(t_mutex *mutex, long *value, long new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

/*
Safely increments a shared long variable using a mutex.
Prevents data races in multi-threaded environments.
*/
void	increment_long(t_mutex *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

bool	simulation_finished(t_table	*table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}