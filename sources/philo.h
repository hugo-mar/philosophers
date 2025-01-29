/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:16:06 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/29 19:27:38 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ANSI escape sequences */
# define RESET		"\033[0m"
# define B			"\033[1m"
# define U			"\033[4m"
# define BLINK		"\033[5m"

# define BLK		"\033[30m"
# define RED		"\033[31m"
# define GRN		"\033[32m"
# define YLW		"\033[33m"
# define BLU		"\033[34m"
# define MGT		"\033[35m"
# define CYN		"\033[36m"
# define WHT		"\033[37m"

# define BG_BLK		"\033[40m"
# define BG_RED		"\033[41m"
# define BG_GRN		"\033[42m"
# define BG_YLW		"\033[43m"
# define BG_BLU		"\033[44m"
# define BG_MGT		"\033[45m"
# define BG_CYN		"\033[46m"
# define BG_WHT		"\033[47m"

# define CLR_SCR		"\033[2J"
# define CLR_LIN		"\033[K"

# define DEBUG_MODE	1

# include <unistd.h>	// write, read
# include <stdlib.h>	// malloc, free
# include <stdio.h>		// printf
# include <string.h>	// memset
# include <sys/time.h>	// usleep, gettimeofday
# include <stdint.h>	// uint64_t
# include <limits.h>	// INT_MAX, INT MIN 
# include <stdbool.h>
# include <errno.h>
# include <pthread.h>	// pthread: create, join, detach
						// pthread_mutex: init, destroy, lock, unlock

// long, porque vamos usar microsseconds no project
// e tudo longs, porque vamos usar getters e setter que beneficiam dessa uniformidade
// é preciso perceber como é que os longs organizam o tempo do getttimeofday (a correspondência de unidades) para peceber divisões e multi por 1000 ou 1000000 nos longs

/*
	Readability
*/
typedef pthread_mutex_t	t_mutex;

typedef enum	e_time
{
	SECONDS,
	MILISSECONDS,
	MICROSSECONDS,
}				t_e_time;

typedef enum	e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
	DIED  ,
}				t_status;

typedef struct s_table t_table;

/*
	Structs
*/
typedef struct s_fork
{
	int		id;						// Used for debugging
	t_mutex	fork;
	bool	fork_mutex_init;
}			t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thr_id;				// A philo is a thread
	t_fork		*first_fork;		// odd-even assignment
	t_fork		*second_fork;		//     "		"
	t_mutex		philo_mutex;		// Used for races with the monitor
	bool		philo_mutex_init;
	long		last_meal_time;		// Allows to see the time passed from last meal
	long		meals_taken;
	bool		full;				// Comeu o max de refeições
	t_table		*table;
}				t_philo;

typedef	struct s_table
{
	long		nbr_philos;			// (argv[1])
	long		time_to_die;		// (argv[2]) //usecs
	long		time_to_eat;		// (argv[3]) //usecs
	long		time_to_sleep;		// (argv[4]) //usecs
	long		max_meals;			// (argv[5]) | It works also as a flag (-1) in case of missing arg (bivalent variable - both a flag and value)
	long		simulation_start;
	long		nbr_running_threads;
	bool		all_treads_created;
	bool		end_simulation;		// triggered when a philo dies or gets full
	pthread_t	monitor;
	t_mutex		print_mutex;
	bool		print_mutex_init;
	t_mutex		table_mutex;
	bool		table_mutex_init;
	t_fork		*forks;				// Array to the forks
	t_philo		*philos;			// Array to the philosophers
}				t_table;

/*
	Functions
*/
// Main functions
int		parse_input(t_table *table, char **argv);
int		data_init(t_table *table);
int		start_dinner(t_table *table);

// Thread functions
void	*dinner_simulation(void *arg);
void	*monitor_simulation(void *arg);

// Print utils
void	print_status(t_philo *philo, t_status status, bool debug);

// Cleanup functions
int		error_free(char	*error_message, t_table *table, int threads_created);
void	free_resources(t_table *table, int initialized_mutexes);

// Getters and setters
bool	get_bool(t_mutex *mutex, bool *value);
void	set_bool(t_mutex *mutex, bool *value, bool new_value);
long	get_long(t_mutex *mutex, long *value);
void	set_long(t_mutex *mutex, long *value, long new_value);
void	increment_long(t_mutex *mutex, long *value);
bool	simulation_finished(t_table	*table);

// Synchronization and chronometration
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mutex *mutex, long *nbr_thrds, long nbr_philos);
long	get_time(t_e_time time_code);
void	precise_usleep(long usleep_time, t_table *table);

#endif