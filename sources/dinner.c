/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:40:42 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/02 23:35:05 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Creates and launches the necessary threads:
- If there is only one philosopher, runs the `lone_philo` function.
- Otherwise, starts the dinner simulation for all philosophers.
- Additionally, starts the monitor thread to check for deaths.
Returns 0 on success, -1 on failure.
*/
static int	launch_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_philos == 1)
	{
		if (pthread_create(&table->philos[0].thr_id, NULL,
				lone_philo, &table->philos[0]) != 0)
			return (-1);
	}
	else
	{
		while (++i < table->nbr_philos)
			if (pthread_create(&table->philos[i].thr_id, NULL,
					dinner_simulation, &table->philos[i]) != 0)
				return (-1);
	}
	if (pthread_create(&table->monitor, NULL, monitor_simulation, table) != 0)
		return (-1);
	return (0);
}

/*
Waits for all philosopher threads and the monitor thread to finish.
Sets 'end_simulation' to true to ensure proper termination.
Returns 0 on success, -1 on failure.
*/
static int	join_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philos)
		if (pthread_join(table->philos[i].thr_id, NULL) != 0)
			return (-1);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	if (pthread_join(table->monitor, NULL) != 0)
		return (-1);
	return (0);
}

/*
Runs the philosopher dinner simulation. Exits if no meals are required.
Launches and synchronizes threads, and waits for their completion.
Errors are handled.
*/
int	start_dinner(t_table *table)
{
	if (table->max_meals == 0)
		return (0);
	if (launch_threads(table) == -1)
		return (error_free("Error: Thread init", table));
	table->simulation_start = get_time(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	if (join_threads(table) == -1)
		return (error_free("Error: Thread join", table));
	return (0);
}
