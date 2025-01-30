/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:31:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/30 23:51:25 by hugo-mar         ###   ########.fr       */
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

bool	all_threads_running(t_mutex *mutex, long *nbr_thrds, long nbr_philos)
{
	bool	ret;

	ret = false;
	(void)mutex;
	pthread_mutex_lock(mutex);
	if (*nbr_thrds == nbr_philos)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/*
To make the system fair
*/
void	desynchronize_philos(t_philo *philo)
{
	if (philo->table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30000, philo->table);
	}
	else
		if (philo->id % 2 != 0)
			ft_think(philo, true);
}
