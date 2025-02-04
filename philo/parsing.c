/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:02:45 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/02/04 14:52:35 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Checks if a char is a space.
*/
static inline bool	is_space(const char chr)
{
	return ((chr >= 9 && chr <= 13) || chr == 32);
}

/*
Checks if a char is a digit.
*/
static inline bool	is_digit(const char chr)
{
	return (chr >= '0' && chr <= '9');
}

/*
Validates if the input is a positive number,
and has 10 significant digits maximum (same as MAX_INT).
*/
static bool	valid_nbr(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!is_digit(*str))
		return (false);
	while (str[i] == '0')
	{
		i++;
		j++;
	}
	while (is_digit(str[i]))
		i++;
	return ((i - j) <= 10);
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
	if (*str == '+')
		str++;
	if (!valid_nbr(str))
		return (-1);
	while (is_digit(*str))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX || *str != '\0')
		return (-1);
	else
		return (nbr);
}

/*
Parses the input. The received time values are converted to microseconds for
uniformity. max_meals acts as a bivalent variable: if no value is provided, 
it is initialized to -1, serving as a flag (-2 is as flag value for an ft_atol
error return).
*/
int	parse_input(t_table *table, char **argv)
{
	table->nbr_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
	{
		table->max_meals = ft_atol(argv[5]);
		if (table->max_meals == -1)
			table->max_meals = -2;
	}
	else
		table->max_meals = -1;
	if (table->time_to_die < (60 * 1000) || table->time_to_eat < (60 * 1000)
		|| table->time_to_sleep < (60 * 1000) || table->nbr_philos <= 0
		|| table->max_meals == -2)
	{
		printf("Invalid arguments to start the simulation\n");
		return (-1);
	}
	return (0);
}
