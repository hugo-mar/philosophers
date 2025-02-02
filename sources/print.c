/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:58:18 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/02 19:28:36 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Prints a detailed debug message for philosopher actions, including fork IDs and
meal count. This function provides extra information useful for debugging.
*/
static void	debug_print(t_philo *philo, t_status status, long elapsed)
{
	if (status == FIRST_FORK)
		printf(WHT"%-6ld "BLU"%d has taken the first fork\t\t\t[fork %d]\n"RST,
			elapsed, philo->id, philo->first_fork->id);
	else if (status == SECOND_FORK)
		printf(WHT"%-6ld "BLU"%d has taken the second fork\t\t\t[fork %d]\n"RST,
			elapsed, philo->id, philo->second_fork->id);
	else if (status == EATING)
		printf(WHT"%-6ld "CYN"%d is eating\t\t\t[meal %ld]\n"RST,
			elapsed, philo->id, philo->meals_taken);
	else if (status == SLEEPING)
		printf(WHT"%-6ld "MGT"%d is sleeping\n"RST, elapsed, philo->id);
	else if (status == THINKING)
		printf(WHT"%-6ld "GRN"%d is thinking\n"RST, elapsed, philo->id);
	else if (status == DIED)
		printf(WHT"%-6ld "RED"%d died\n"RST, elapsed, philo->id);
}

/*
Prints the current status of a philosopher with time synchronization.
Uses a mutex to ensure that messages are printed sequentially.
If debug mode is enabled, additional details are shown.
*/
void	print_status(t_philo *philo, t_status status, bool debug)
{
	long	elapsed;

	if (simulation_finished(philo->table) || get_bool(&philo->philo_mutex,
			&philo->full))
		return ;
	elapsed = get_time(MILLISECONDS) - philo->table->simulation_start;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (debug)
		debug_print(philo, status, elapsed);
	else
	{
		if (status == FIRST_FORK || status == SECOND_FORK)
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
