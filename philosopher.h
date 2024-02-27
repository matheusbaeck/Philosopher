/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/02/27 13:59:54 by math             ###   ########.fr       */
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

typedef struct s_philo_init
{
	int				phid;
	long int		time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				notepme;
}					t_philo_init;


typedef struct s_philo
{
	long int		born_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				notepme;
	pthread_mutex_t	*fork[2];
	int				(*last_act)(void *param);
	int				phid;
	int				name;
	long int		time;
	long int		last_meal;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	fork[MAX_PHILO];
	pthread_t		routine[MAX_PHILO];
	t_philo			philo[MAX_PHILO];
	int				n_philo;
}	t_data;


//PARSING
int			check_entry(int argc, char **argv);
//PHILO
long int	get_time(t_philo *philo);
int			is_alive(t_philo *philo);
void		*philo_loop(void *philo);
//ACTIONS
int			think(void*philo);
int			eat(void *philo);
int			psleep(void *philo);
int			die(void *philo);
//UTILS
long int	get_delta_time(t_philo *philo);
int			sleep_ms(int mseconds);

#endif
