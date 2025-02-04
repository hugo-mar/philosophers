/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronometration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:45:13 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/02 16:07:06 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Gets the current time in the specified unit (SECONDS, MILLISECONDS, or
MICROSECONDS). Returns the time value in the requested unit, or -1 in case of
failure.
*/
long	get_time(t_e_time time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		return (-1);
}

/*
Sleeps with high precision. Uses usleep() for longer wait times and busy-waiting
(spinlock) for short durations to minimize oversleeping.
The function terminates early if the simulation has finished.
*/
void	precise_usleep(long usleep_time, t_table *table)
{
	long	start;
	long	current;
	long	remaining;

	start = get_time(MICROSECONDS);
	current = start;
	while ((current - start) < usleep_time)
	{
		if (simulation_finished(table))
			break ;
		current = get_time(MICROSECONDS);
		remaining = usleep_time - (current - start);
		if (remaining > 1000)
			usleep(remaining / 2);
		else
			while ((get_time(MICROSECONDS) - start) < usleep_time)
				;
	}
}
