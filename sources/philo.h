/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:16:06 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/01/31 18:09:25 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
	ANSI escape sequences
*/
# define RST		"\033[0m"
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
# define CLR_SCR	"\033[2J"
# define CLR_LIN	"\033[K"

/*
	Debugging mode
*/
# define DEBUG_MODE	0

/*
	Libraries
*/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h> 
# include <stdbool.h>
# include <pthread.h>

/*
	Readability typedef's
*/
typedef pthread_mutex_t	t_mutex;

typedef enum e_time
{
	SECONDS,
	MILLISSECONDS,
	MICROSSECONDS,
}				t_e_time;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
	DIED,
}				t_status;

/*
	Structs
*/
typedef struct s_table	t_table;

typedef struct s_fork
{
	int		id;
	t_mutex	fork;
	bool	fork_mutex_init;
}			t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thr_id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mutex		philo_mutex;
	bool		philo_mutex_init;
	long		last_meal_time;
	long		meals_taken;
	bool		full;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		nbr_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_meals;
	long		simulation_start;
	long		nbr_running_threads;
	bool		all_treads_created;
	bool		end_simulation;
	pthread_t	monitor;
	t_mutex		print_mutex;
	bool		print_mutex_init;
	t_mutex		table_mutex;
	bool		table_mutex_init;
	t_fork		*forks;
	t_philo		*philos;
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
void	*lone_philo(void *arg);
void	ft_eat(t_philo	*philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo, bool pre_simulation);

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
void	desynchronize_philos(t_philo *philo);
long	get_time(t_e_time time_code);
void	precise_usleep(long usleep_time, t_table *table);

#endif