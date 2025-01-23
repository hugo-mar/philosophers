/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:16:06 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/23 17:38:29 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// write, read
#include <stdlib.h>		// malloc, free
#include <stdio.h>		// printf
#include <string.h>		// memset
#include <sys/time.h>	// usleep, gettimeofday
#include <stdint.h>		// uint64_t
#include <limits.h>		// INT_MAX, INT MIN 
#include <stdbool.h>
#include <errno.h>
#include <pthread.h>	// pthread: create, join, detach
						// pthread_mutex: init, destroy, lock, unlock
/*
	ANSI escape sequences
*/
#define RESET		"\033[0m"
#define B			"\033[1m"
#define U			"\033[4m"
#define BLINK		"\033[5m"

#define BLK			"\033[30m"
#define RED			"\033[31m"
#define GRN			"\033[32m"
#define YLW			"\033[33m"
#define BLU			"\033[34m"
#define MGT			"\033[35m"
#define CYN			"\033[36m"
#define WHT			"\033[37m"

#define BG_BLK		"\033[40m"
#define BG_RED		"\033[41m"
#define BG_GRN		"\033[42m"
#define BG_YLW		"\033[43m"
#define BG_BLU		"\033[44m"
#define BG_MGT		"\033[45m"
#define BG_CYN		"\033[46m"
#define BG_WHT		"\033[47m"

#define CLR_SCR		"\033[2J"
#define CLR_LIN		"\033[K"

// long, porque vamos usar microsseconds no project

/*
	Readability
*/
typedef pthread_mutex_t	t_mtx;

typedef struct s_table t_table;

/*
	Structs
*/
typedef struct s_fork
{
	int		id;
	t_mtx	fork;
}			t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thr_id;				// A philo is a thread
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	long		last_meal_time;		// Allows to see the time passed from last meal
	long		meals_taken;
	bool		full;				// Comeu o max de refeições
}				t_philo;

typedef	struct s_table
{
	long		nbr_philos;			// (argv[1])
	long		time_to_die;		// (argv[2])
	long		time_to_eat;		// (argv[3])
	long		time_to_sleep;		// (argv[4])
	long		max_meals;			// (argv[5]) | It works also as a flag (-1) in case of missing arg (bivalent variable - both a flag and value)
	long		start_sim_time;	
	bool		end_simulation;		// triggered when a philo dies or gets full
	t_fork		*forks;				// Array to the forks
	t_philo		*philos;			// Array to the philosophers
}				t_table;

/*
	Functions
*/
int		parse_input(t_table *table, char **argv);
int		data_init(t_table *table);
void	free_resources(t_table *table, int initialized_mutexes);



