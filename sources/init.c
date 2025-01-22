/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:06:49 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/22 23:29:52 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int nbr_philos;

	nbr_philos = philo->table->nbr_philos;

	philo->first_fork = &forks[(philo_position + 1) % nbr_philos];			// No header mudou left->first e right ->second
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)			// Ele disse odd mas corrigiu para even
	{
		philo->first_fork = &forks[philo_position];							// aqui trocou o right-fork para first-fork
		philo->second_fork = &forks[(philo_position + 1) % nbr_philos];		// e aqui trocou o left-fork para second-fork
	}
}

/*
Initializes the philosopher data (t_philo).
Returns 0 in case of sucess and -1 in case of error
*/
static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philosopher;

	i = -1;
	while (++i < table->nbr_philos)
	{
		philosopher = table->philos + i;
		philosopher->id = i + 1;
		philosopher->meals_taken = 0;
		philosopher->full = false;
		philosopher->table = table;
	
		assign_forks(philosopher, table->forks, i);
	}
	return (0);
}

/*
Initializes the table data (t_table).
Returns 0 in case of sucess and -1 in case of error
*/
int	data_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
	if (!table->philos || !table->forks)
		return (-1);
	i = -1;
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (-1);
		table->forks[i].id = i;						// used for debugging
	}
	return (philo_init(table));
}
