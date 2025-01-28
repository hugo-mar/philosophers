/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:31:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/28 14:37:58 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
A spinlock to synchronize all the threads.
*/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_treads_created))
		;
}

/*
Returns the current time in the requested time unit, or -1 in case of errror.
*/
long	get_time(t_e_time time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILISSECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		return (-1);
}

/*
uSleeps whith precision. For longer times uses usleep and for precision uses
busy-wait (splinlock).
*/
void	precise_usleep(long usleep_time, t_table *table)
{
	long	start;
	long	current;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSSECONDS);
	current = start;

	elapsed = 0;
	
	while ((current - start) < usleep_time)
	{
		if (simulation_finished(table))
			break;
		current = get_time(MICROSSECONDS);
		elapsed = current - start;
		remaining = usleep_time - elapsed;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
			while ((get_time(MICROSSECONDS) - start) < usleep_time)
			;
	}
}
