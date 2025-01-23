/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:58:49 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/23 15:38:20 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argv) == -1 && printf("Invalid arguments\n"))
			return (1);
		if (data_init(&table) == -1)
			return (1);
		//dinner_simulation();
		free_resources(&table, table.nbr_philos);	// When philos all are full
	}												// or when one philo dies
	else
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	return (0);
}
