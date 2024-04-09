/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/09 18:37:05 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h> //ft_atoi
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// #define	T_LOCK 50;
// #define T_UNLOCK 10;

enum				e_action
{
	THINK = 42,
	EAT = 21,
	SLEEP = 84,
};

enum				e_status
{
	DEAD = -42,
	FINISH = 420,
};

typedef struct s_philo_init
{
	int				phid;
	long int		time_zero;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				notepme;
	int				*status;
	pthread_mutex_t	*mutex_philo_att;
	pthread_mutex_t	*mutex_status;
	pthread_mutex_t	*mutex_print;
}					t_philo_init;

typedef struct s_philo
{
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*mutex_philo_att;
	pthread_mutex_t	*mutex_status;
	pthread_mutex_t	*mutex_print;
	long int		time_zero;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		last_meal;
	int				notepme;
	int				phid;
	int				name;
	int				*status;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutex_philo_att;
	pthread_mutex_t	mutex_status;
	pthread_mutex_t	mutex_print;
	pthread_t		*routine;
	t_philo			*philo;
	long int		time_zero;
	int				n_philo;
	int				time_to_die;
	int				status;
}					t_data;

//INIT
int					init(int argc, char **argv, t_data *dt);
//PARSING
int					check_entry(int argc, char **argv);
//PHILO
long int			get_print_time(t_philo *self);
void				*philo_loop(void *philo);
//MUTEX_PHILO_ATT
long int			get_last_meal(t_philo *self);
int					set_last_meal(t_philo *self, long int val);
int					get_notepme(t_philo *self);
int					add_notepme(t_philo *self, int val);
//MUTEX_STATUS
int					get_status(t_philo *self);
int					set_status(t_philo *self, int val);
void				add_status(t_philo *self, int val);
void				print_safe(char *str, t_philo *self);
//ACTIONS
int					think(t_philo *ph);
int					eat(t_philo *ph);
int					philo_sleep(t_philo *ph);
//UTILS
int					sleep_ms(int mseconds);
long int			get_time(void);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
int					is_alldigit(char *str);
int					ft_atoi(const char *str);

#endif
