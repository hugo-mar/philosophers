/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_and_think.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:55:37 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/02 23:47:28 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Handles the eating phase of a philosopher:
- Takes both forks in the correct order and prints their status.
- Updates the philosopher's last meal time and prints the eating status.
- Increments the meal count and waits for the eating time to finish.
- If the maximum number of meals is reached, marks the philosopher as full.
- Releases both forks after finishing the meal.
*/
void	ft_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(philo, FIRST_FORK, DEBUG_MODE);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(philo, SECOND_FORK, DEBUG_MODE);
	set_long(&philo->philo_mutex,
		&philo->last_meal_time, get_time(MILLISECONDS));
	print_status(philo, EATING, DEBUG_MODE);
	philo->meals_taken++;
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_taken == philo->table->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

/*
Prints sleep status and makes the philosopher sleep for the required time.
*/
void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING, DEBUG_MODE);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

/*
Handles the thinking phase of a philosopher:
- If pre_simulation is true, skips printing the thinking status.
- On even nbr of philos, returns immediately (no additional delay needed).
- On odd nbr of philos, introduces a calculated delay before the next action
  to improve fairness and avoid simultaneous fork grabbing.
*/
void	ft_think(t_philo *philo, bool pre_simulation)
{
	int	t_think;

	if (!pre_simulation)
		print_status(philo, THINKING, DEBUG_MODE);
	if ((philo->table->nbr_philos % 2) == 0)
		return ;
	t_think = (philo->table->time_to_eat * 2) - philo->table->time_to_sleep;
	if (t_think > 0)
		precise_usleep(t_think * 0.42, philo->table);
}
