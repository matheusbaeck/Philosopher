/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/05 21:39:40 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h> //atoi
#include <sys/time.h>
#include <signal.h>

// #define	T_LOCK 50;
// #define T_UNLOCK 10;

enum	e_action
{
	THINK = 42,
	EAT = 21,
	SLEEP = 84,
};

enum	e_status
{
	DEAD = -42,
	FINISH = 420,
};

typedef struct s_philo_exit
{
	int				phid;
	int 			name;
	int				status;
	long int		time_of_death;
}					t_philo_exit;


typedef struct s_philo_init
{
	int				phid;
	long int		time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				notepme;
	int				*status;
	pthread_mutex_t	*mutex;
	t_philo_exit	*exs;
}					t_philo_init;

typedef struct s_philo
{
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*mutex;
	long int		time;
	long int		time_zero;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		last_meal;
	int				notepme;
	int				last_act;
	int				phid;
	int				name;
	int				*status;
	t_philo_exit	*exs;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
	pthread_t		*routine;
	t_philo			*philo;
	t_philo_exit	*exs;
	long int		time_zero;
	int				n_philo;
	int				time_to_die;
	int				status;
}					t_data;


//PARSING
int			check_entry(int argc, char **argv);
//PHILO
void		set_time(t_philo *philo);
int			is_alive(t_philo *philo);
void		*philo_loop(void *philo);
//ACTIONS
int			think(t_philo *ph);
int			eat(t_philo *ph);
int			philo_sleep(t_philo *ph);
void		*die(t_philo *ph);
//UTILS
long int	get_delta_time(t_philo *philo);
int			sleep_ms(int mseconds);
void		dbfree(void **ptr);
void		set_zero(t_philo *philo, int size, long int time_zero);
long int	get_time(void);

#endif
