/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:06:49 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/29 08:23:30 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Assigns forks to philosophers. To avoid deadlocks,
odd philos take fist the left fork, even philos take first the right one.
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int nbr_philos;

	nbr_philos = philo->table->nbr_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % nbr_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % nbr_philos];
		philo->second_fork = &forks[philo_position];
	}
}

/*
Initializes the philosopher data (t_philo).
Returns 0 in case of sucess and -1 in case of error.
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
			return(error_free("Error: Failed to init a philo mutex",
				table, table->nbr_philos));
	}
	return (0);
}	

/*
 Initiales table struct variables.
 Returns exit status code for success or failure.
*/
static int	table_init(t_table *table)
{
	table->nbr_running_threads = 0;
	table->all_treads_created = false;
	table->end_simulation = false;
	table->table_mutex_init = false;
	table->philos = NULL;
    table->forks = NULL;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->philos || !table->forks)
		return (-1);
	return (0);
}

/*
Executes the functions to init table and philo data, and mutexes.
Returns 0 in case of sucess and -1 in case of error.
*/
int	data_init(t_table *table)
{
	int	i;

	i = -1;
	if (table_init(table) == -1)
		return (error_free("Error: Memory allocation failed", table, 0));
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (error_free("Error: Failed to init table mutex", table, 0));
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (error_free("Error: Failed to init write mutex", table, 0));
	table->table_mutex_init = true;
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (error_free("Error: Failed to init fork mutex", table, i));
		table->forks[i].id = i;						// used for debugging
	}
	return (philo_init(table));
}
