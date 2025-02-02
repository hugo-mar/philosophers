/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:31:32 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/02 17:30:25 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
A spinlock to synchronize all the threads.
*/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_created))
		;
}

/*
Checks if all threads are running safely using a mutex.
*/
bool	all_threads_running(t_mutex *mutex, long *nbr_thrds, long nbr_philos)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*nbr_thrds == nbr_philos)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/*
Introduces a slight desynchronization between philosophers:
- If the number of philos is even, philosophers with an even ID sleep briefly.
- If the number of philos is odd, odd-numbered philosophers think before acting.
This prevents all philosophers from trying to take forks at the same time.
*/
void	desynchronize_philos(t_philo *philo)
{
	if (philo->table->nbr_philos % 2 == 0 && philo->id % 2 == 0)
		precise_usleep(30000, philo->table);
	else if (philo->table->nbr_philos % 2 != 0 && philo->id % 2 != 0)
		ft_think(philo, true);
}
