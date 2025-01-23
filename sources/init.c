/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:06:49 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/23 18:02:09 by hugo-mar         ###   ########.fr       */
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
	}
	return (0);
}

void	free_resources(t_table *table, int initialized_mutexes)
{
    int	i;

	i = -1;
	if (table->philos)
    {
        free(table->philos);
        table->philos = NULL;
    }
    if (table->forks)
    {
        while (++i < initialized_mutexes)
            pthread_mutex_destroy(&table->forks[i].fork);
        free(table->forks);
        table->forks = NULL;
    }
}

/*
Initializes the table data (t_table).
Returns 0 in case of sucess and -1 in case of error.
*/
int	data_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->philos || !table->forks)
	{
		printf("Error: Memory allocation failed\n");
		free_resources(table, 0);
		return (-1);
	}
	i = -1;
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			printf("Error: Mutex initialization failed at index %d\n", i);
			free_resources(table, i);
			return (-1);
		}
		table->forks[i].id = i;						// used for debugging
	}
	return (philo_init(table));
}
