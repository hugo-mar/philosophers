/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:30:17 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/01 13:43:51 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Frees all the resources allocated and created.
*/
void	free_resources(t_table *table)
{
	int	i;

	i = -1;
	if (table->philos)
	{
		while (++i < table->nbr_philos)
			if (table->philos[i].philo_mutex_init)
				pthread_mutex_destroy(&table->philos[i].philo_mutex);
		free(table->philos);
		table->philos = NULL;
	}
	i = -1;
	if (table->forks)
	{
		while (++i < table->nbr_philos)
			if (table->forks[i].fork_mutex_init)
				pthread_mutex_destroy(&table->forks[i].fork);
		free(table->forks);
		table->forks = NULL;
	}
	if (table->table_mutex_init)
		pthread_mutex_destroy(&table->table_mutex);
	if (table->print_mutex_init)
		pthread_mutex_destroy(&table->print_mutex);
}

/*
Prints an error message and frees allocated resources in case of failure.
Returns -1 to indicate an error.
*/
int	error_free(char	*error_message, t_table *table)
{
	printf("%s\n", error_message);
	free_resources(table);
	return (-1);
}
