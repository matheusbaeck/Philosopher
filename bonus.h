/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/11 21:28:36 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// #define	T_LOCK 50;
// #define T_UNLOCK 10;

enum				e_action
{
	THINK = 42,
	FORK_ONE = 11,
	FORK_TWO = 22,
	EAT = 21,
	SLEEP = 84,
};

enum				e_status
{
	DEAD = -42,
	FINISH = 420,
};

typedef struct s_philo
{
	sem_t			*semaphore;
	int				phid;
	long int		time_zero;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				notepme;
	int				name;
	long int		last_meal;
	int				last_act;
}					t_philo;

//PARSING
int			ft_strlen(const char *s);
int			ft_isdigit(int c);
int			is_alldigit(char *str);
int			ft_atoi(const char *str);
int			check_entry(int argc, char **argv);
//TIME
int			sleep_ms(int mseconds);
long int	get_time(void);
long int	get_print_time(t_philo *self);
//INIT
void		init_philo(int argc, char **argv, pid_t *pid, int n_philo, sem_t *semaphore);
int			init(pid_t **pid, int n_philo, sem_t **semaphore);
//WAIT
void		wait_philos(pid_t *pid, int n_philo);
//PHILO
void 		philo_task(t_philo ph);
void		philo_loop(t_philo *ph);

#endif
