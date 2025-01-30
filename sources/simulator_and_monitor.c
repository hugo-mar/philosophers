/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_and_monitor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:00:46 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/30 23:39:51 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_table	*table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISSECONDS));
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

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISSECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

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

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISSECONDS));
	increment_long(&philo->table->table_mutex,
		&philo->table->nbr_running_threads);
	print_status(philo, FIRST_FORK, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
