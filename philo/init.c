/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:06:49 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/01 13:37:49 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Assigns forks to philosophers in a way that prevents deadlocks:
- Odd philosophers take the left fork first, then the right.
- Even philosophers take the right fork first, then the left.
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_array_pos)
{
	int	nbr_philos;

	nbr_philos = philo->table->nbr_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_array_pos];
		philo->second_fork = &forks[(philo_array_pos + 1) % nbr_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_array_pos + 1) % nbr_philos];
		philo->second_fork = &forks[philo_array_pos];
	}
}

/*
Initializes the philosopher structures (t_philo), including their IDs,
meal counters, and assigned forks.
Returns 0 on success and -1 if a philosopher mutex fails to initialize.
*/
static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_taken = 0;
		philo->full = false;
		philo->table = table;
		assign_forks(philo, table->forks, i);
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (error_free("Error: Failed to init a philo mutex", table));
		philo->philo_mutex_init = true;
	}
	return (0);
}

/*
Initializes the table structure (t_table), setting default values for 
simulation control variables and allocating memory for philosophers and forks.
Returns 0 on success or -1 if memory allocation fails.
*/
static int	table_init(t_table *table)
{
	int	i;

	i = -1;
	table->nbr_running_threads = 0;
	table->all_threads_created = false;
	table->end_simulation = false;
	table->table_mutex_init = false;
	table->print_mutex_init = false;
	table->philos = NULL;
	table->forks = NULL;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->philos || !table->forks)
		return (-1);
	while (++i < table->nbr_philos)
	{
		table->philos[i].philo_mutex_init = false;
		table->forks[i].fork_mutex_init = false;
	}
	return (0);
}

/*
Initializes all data structures, allocates memory, and sets up mutexes for 
synchronization. Calls 'table_init' and 'philo_init'.
Returns 0 on success or -1 if any initialization step fails.
*/
int	data_init(t_table *table)
{
	int	i;

	i = -1;
	if (table_init(table) == -1)
		return (error_free("Error: Memory allocation failed", table));
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (error_free("Error: Failed to init table mutex", table));
	table->table_mutex_init = true;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (error_free("Error: Failed to init write mutex", table));
	table->print_mutex_init = true;
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (error_free("Error: Failed to init fork mutex", table));
		table->forks[i].fork_mutex_init = true;
		table->forks[i].id = i;
	}
	return (philo_init(table));
}
