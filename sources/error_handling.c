/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:30:17 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/25 10:44:49 by hugo-mar         ###   ########.fr       */
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
        free(table->philos);
        table->philos = NULL;
    }
	if (table->table_mutex_init)
		pthread_mutex_destroy(&table->table_mutex);
    if (table->forks)
    {
        while (++i < threads_created)
            pthread_mutex_destroy(&table->forks[i].fork);
        free(table->forks);
        table->forks = NULL;
    }
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
