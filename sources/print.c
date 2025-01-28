/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:58:18 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/28 15:43:09 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	debug_print(t_philo *philo, t_status status, long elapsed)
{
	if (status == FIRST_FORK)
		printf(WHT"%-6ld "RESET"%d has taken the first fork\t\t\t[fork %d]\n",
			elapsed, philo->id, philo->first_fork->id);
	else if (status == SECOND_FORK)
		printf(WHT"%-6ld "RESET"%d has taken the second fork\t\t\t[fork %d]\n",
			elapsed, philo->id, philo->second_fork->id);
	else if (status == EATING)
		printf(WHT"%-6ld "RESET"%d is eating\t\t\t[meal %ld]\n", elapsed, philo->id,
			philo->meals_taken);
	else if (status == SLEEPING)
		printf(WHT"%-6ld "RESET"%d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf(WHT"%-6ld "RESET"%d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(WHT"%-6ld "RESET"%d died\n", elapsed, philo->id);
}

void	print_status(t_philo *philo, t_status status, bool debug)
{
	long	elapsed;

	if (simulation_finished(philo->table) || philo->full) 	// philo->full threadsafe???
		return ;
	elapsed = get_time(MILISSECONDS) - philo->table->simulation_start;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (debug)
		debug_print(philo, status, elapsed);
	else
	{
		if (status == FIRST_FORK || status == SECOND_FORK)
			printf(WHT"%-6ld "RESET"%d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf(WHT"%-6ld "RESET"%d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf(WHT"%-6ld "RESET"%d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf(WHT"%-6ld "RESET"%d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(WHT"%-6ld "RESET"%d died\n", elapsed, philo->id);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
