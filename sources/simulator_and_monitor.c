/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_and_monitor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:00:46 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/03 11:58:31 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Checks if the simulation has ended.
Returns true if the simulation should stop, false otherwise.
*/
bool	simulation_finished(t_table	*table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

/*
Main routine for philosopher threads.
- Waits for all threads to be ready.
- Records the philosopher's initial meal time.
- Synchronizes with other philosophers.
- Loops through eating, sleeping, and thinking until the simulation ends.
*/
void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	increment_long(&philo->table->table_mutex,
		&philo->table->nbr_running_threads);
	desynchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo, false);
	}
	return (NULL);
}

/*
Checks if a philosopher has exceeded their time to die.
Returns true if the philosopher has died, false otherwise.
*/
static bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	return (elapsed > (philo->table->time_to_die / 1000));
}

/*
Monitors the simulation to detect philosopher deaths.
- Waits until all threads are running.
- Continuously checks if any philosopher has died.
- Ends the simulation if a death is detected.
*/
void	*monitor_simulation(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (!all_threads_running(&table->table_mutex,
			&table->nbr_running_threads, table->nbr_philos))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->nbr_philos && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				print_status(table->philos + i, DIED, DEBUG_MODE);
				set_bool(&table->table_mutex, &table->end_simulation, true);
			}
		}
	}
	return (NULL);
}

/*
Handles the special case where there is only one philosopher.
- Waits for synchronization.
- Picks up the only available fork.
- Waits until the simulation ends.
*/
void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	increment_long(&philo->table->table_mutex,
		&philo->table->nbr_running_threads);
	print_status(philo, FIRST_FORK, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
