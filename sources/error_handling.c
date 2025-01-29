/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:30:17 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/29 19:27:43 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Frees all the resources allocated and created.
*/
void	free_resources(t_table *table, int threads_created)
{
	int	i;

	i = -1;
	if (table->philos)
	{
		while (++i < threads_created)
			if (table->philos[i].philo_mutex_init)
				pthread_mutex_destroy(&table->philos[i].philo_mutex);
		free(table->philos);
		table->philos = NULL;
	}
	i = -1;
	if (table->forks)
	{
		while (++i < threads_created)
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
Prints a costum error message and frees the resources in case of error.
It recieves the number of threads created. Returns an error code (-1).
*/
int	error_free(char	*error_message, t_table *table, int threads_created)
{
	printf("%s\n", error_message);
	free_resources(table, threads_created);
	return (-1);
}
