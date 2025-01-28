/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:40:42 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/28 15:26:03 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING, DEBUG_MODE);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

/*
Prints fork status, updates the last meal time and number of meals taken
Prints eat status and waits for current meal to end.
If the maximum number of meals is reached, the corresponding flag is set.
*/
static void	ft_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(philo, FIRST_FORK, DEBUG_MODE);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(philo, SECOND_FORK, DEBUG_MODE);
	set_long(&philo->philo_mutex,
		&philo->last_meal_time, get_time(MILISSECONDS));
	philo->meals_taken++;
	print_status(philo, EATING, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_taken == philo->table->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

static void	ft_think(t_philo *philo)
{
	print_status(philo, THINKING, DEBUG_MODE);
}

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);

	while (!simulation_finished(philo->table))
	{
		if (philo->full)			//Make safe?
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	

	return (NULL);
}


/*
Starts the dinner. Handles 0 or 1 philosopher situation. Creates all threads,
running the dinner simulation. Waits for all them to join before finish.
*/
int	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->max_meals == 0)
		return (0);
	// if (table->max_meals == 1)
	// 	/* ad_hoc_ft */;										// To do
	while (++i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].thr_id, NULL, dinner_simulation,
			&table->philos[i]) != 0)
			return (error_free("Error: Thread init", table, table->nbr_philos));
	}
	table->simulation_start = get_time(MILISSECONDS);
	set_bool(&table->table_mutex, &table->all_treads_created, true);
	i = -1;
	while (++i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].thr_id, NULL) != 0)
			return (error_free("Error: Thread join", table, table->nbr_philos));
	}
	return (0);
}
