/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/12/23 16:16:04 by baeck            ###   ########.fr       */
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
#include <signal.h> //kill

#define MAX_PHILO 10
#define	T_LOCK 50;
#define T_UNLOCK 10;

enum e_status
{
	NOT_INIT = 2,
	THK = 1,
	EAT = 42,
	SLP = 0,
	DEAD = -1,
	FINISH_EATING = -2
};

enum e_turn
{
	BLUE = 420,
	GREEN = 2,
	YELLOW = 1,
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
	int				name;
	int				*turn; //read
	int				*status; //write
	int				i_eat;
	int				must_eat;
}	t_philo;

typedef struct s_controller
{
	int				n_philo;
	int				*notepme;
	int				*philo_status; //read
	int				*turn; //write
	int				n_groups;
	pthread_t		*thread;
}	t_controller;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_t		*thread;
	t_philo			*philo;
	t_controller	*controller;
}	t_data;



//INIT
void	philo_init(t_philo *philo, t_philo param, int *must_eat, int i);
void	controller_init(int argc, char **argv,
	t_controller *controller, int n_philo);
int		init(int argc, char **argv, t_data *dt);
//PHILO
int		update_time(t_philo *philo);
void	*philo_loop(void *philo);
//CONTROLLER
void	set_group_turn(t_controller *controller, int j);
void	*controller_loop(void *controller);
//ACTIONS
int		think(t_philo *philo);
int		eat(t_philo *philo);
int		psleep(t_philo *philo);
int		die(t_philo *philo);
//UTILS
int		lock_fork(t_philo *philo);
int		ft_try_lock(pthread_mutex_t *mutex, int wait_time);
void	*try_lock_fail(void *param);
void	*try_lock_sucess(void *param);
int		try_unlock(t_philo *philo);
int		pwait(int mseconds);

#endif
