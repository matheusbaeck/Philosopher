/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2023/09/13 12:57:59 by math42           ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_mutex_t	*fork[2];
	long int		born_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				(*last_act)(void *param);
	int				number_of_times_each_philosopher_must_eat;
	int				name;
	long int		time;
	long int		last_meal;
	int				div;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	fork[MAX_PHILO];
	pthread_t		routine[MAX_PHILO];
	t_philo			philo[MAX_PHILO];
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}	t_data;


//PHILO
void	philo_init(t_philo *dest, t_philo philo);
int		get_time(t_philo *philo);
int		set_forks(t_data *dt);
void	*philo_loop(void *philo);
//ACTIONS
int		think(void*philo);
int		eat(void *philo);
int		psleep(void *philo);
int		die(void *philo);
//UTILS
int	try_lock(t_philo *philo);
int	try_unlock(t_philo *philo);
int	pwait(int mseconds);

#endif
