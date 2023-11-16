/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/11/16 15:00:26 by math42           ###   ########.fr       */
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

#define MAX_PHILO 10
#define	T_LOCK 50;
#define T_UNLOCK 10;

enum e_status
{
	THK = 42,
	EAT = 1,
	SLP = 0,
	DEAD = -1,
	GREEN = 1,
	RED = 0
};

typedef struct s_philo
{
	pthread_mutex_t	*fork[2];
	long int		born_time;
	long int		time;
	long int		last_meal;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				(*last_act)(void *param);
	int				name;
	int				*turn;
	int				*status; //-1 dead, 0 no forks, 42 2 forks
}	t_philo;

typedef struct s_controller
{
	int				n_philo;
	int				*notepme;
	int				*traffic_control;
	int				*turn;
	int				n_groups;
}	t_controller;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_t		*routine;
	t_philo			*philo;
	t_controller	*controller;
}	t_data;


//PHILO
void	philo_init(t_philo *philo, t_philo param);
int		get_time(t_philo *philo);
int		set_forks(t_data *dt, int n_philo);
void	*philo_loop(void *philo);
//CONTROLLER
void	controller_init(t_controller *controller, int n_philo);
void	set_group_turn(t_controller *controller, int j);
void	*controller_loop(void *controller);
//ACTIONS
int		think(void*philo);
int		eat(void *philo);
int		psleep(void *philo);
int		die(void *philo);
//UTILS
int		lock_fork(t_philo *philo);
int		try_lock(pthread_mutex_t *mutex);
void	*try_lock_fail(void *param);
void	*try_lock_sucess(void *param);
int		try_unlock(t_philo *philo);
int		pwait(int mseconds);

#endif
