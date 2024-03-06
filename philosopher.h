/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/06 11:58:38 by math             ###   ########.fr       */
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
	pthread_mutex_t	*mutex_lstmeal;
	pthread_mutex_t	*mutex_status;
	t_philo_exit	*exs;
}					t_philo_init;

typedef struct s_philo
{
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*mutex_lstmeal;
	pthread_mutex_t	*mutex_status;
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
	pthread_mutex_t	mutex_lstmeal;
	pthread_mutex_t	mutex_status;
	pthread_t		*routine;
	t_philo			*philo;
	t_philo_exit	*exs;
	long int		time_zero;
	int				n_philo;
	int				time_to_die;
	int				status;
}					t_data;

typedef struct s_set_last_meal
{
	t_philo			*ph;
	long int		val;
}					t_set_last_meal;


//PARSING
int			check_entry(int argc, char **argv);
//PHILO
void		set_time(t_philo *self);
long int	get_print_time(t_philo *self);

//MUTEX_GETSET
long int	get_last_meal(t_philo *self);
int			get_status(t_philo *self);
void		*set_last_meal_t(void *void_param);
void		set_last_meal(t_philo *self, long int val);
void		set_status(t_philo *self, int val);
void		add_status(t_philo *self, int val);

void		*philo_loop(void *philo);
//ACTIONS
int			think(t_philo *ph);
int			eat(t_philo *ph);
int			philo_sleep(t_philo *ph);
void		*die(t_philo *ph);
//UTILS
int			sleep_ms(int mseconds);
void		dbfree(void **ptr);
void		set_zero(t_philo *philo, int size, long int time_zero);
long int	get_time(void);

#endif
