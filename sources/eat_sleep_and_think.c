/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_and_think.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:55:37 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/31 11:29:50 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Prints fork status, updates the last meal time and number of meals taken
Prints eat status and waits for current meal to end.
If the maximum number of meals is reached, the corresponding flag is set.
*/
void	ft_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(philo, FIRST_FORK, DEBUG_MODE);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(philo, SECOND_FORK, DEBUG_MODE);
	set_long(&philo->philo_mutex,
		&philo->last_meal_time, get_time(MILLISSECONDS));
	philo->meals_taken++;
	print_status(philo, EATING, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_taken == philo->table->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING, DEBUG_MODE);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

void	ft_think(t_philo *philo, bool pre_simulation)
{
	int	t_think;

	if (!pre_simulation)
		print_status(philo, THINKING, DEBUG_MODE);
	if ((philo->table->nbr_philos % 2) == 0)
		return ;
	t_think = (philo->table->time_to_eat * 2) - philo->table->time_to_sleep;
	if (t_think < 0)
		return ;
	else
		precise_usleep(t_think * 0.42, philo->table);
}
