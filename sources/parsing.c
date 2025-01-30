/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:02:45 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/30 18:05:13 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Checks if a char is a space
*/
static inline bool	is_space(const char chr)
{
	return ((chr >= 9 && chr <= 13) || chr == 32);
}

/*
Checks if a char is a digit
*/
static inline bool	is_digit(const char chr)
{
	return (chr >= '0' && chr <= '9');
}

/*
Checks if a number is valid
*/
static bool	valid_nbr(const char *str)
{
	int	i;

	i = 0;
	if (!is_digit(*str))
		return (false);
	while (is_digit(str[i]))
		i++;
	return (i <= 10);
}

/*
Returns a positive long between 0 and MAX_INT, or -1 in case of error
*/
static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	while (is_space(*str))
		str++;
	while (*str == '+')
		str++;
	if (!valid_nbr(str))
		return (-1);
	while (is_digit(*str))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX)
		return (-1);
	else
		return (nbr);
}

/*
Parses the input. The recieved time values will be converted to usecs for
uniformity. Max_meals works as a bivalent variable. If não value recieved it's
initiated with -1, working also as a flag,
*/
int	parse_input(t_table *table, char **argv)
{
	table->nbr_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	if (table->time_to_die < (60 * 1000) || table->time_to_eat < (60 * 1000)
		|| table->time_to_sleep < (60 * 1000) || table->nbr_philos == 0)
		return (-1);
	else
		return (0);
}
