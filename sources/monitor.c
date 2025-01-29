/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:00:46 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/29 12:23:48 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILISSECONDS) - get_long(&philo->philo_mutex,
		&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_simulation(void *arg)
{
	int	i;
	t_table	*table;

	table = (t_table *)arg;
	while (!all_threads_running(&table->table_mutex,
		&table->nbr_running_threads, table->nbr_philos))
		;
	while(!simulation_finished(table))
	{
		i = -1;
		while (++i < table->nbr_philos && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				print_status(table->philos + i,DIED, DEBUG_MODE);
				set_bool(&table->table_mutex, &table->end_simulation, true);
			}
		}
	}
	return (NULL);
}