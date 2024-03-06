/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/03/06 12:27:15 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	think(t_philo *ph)
{
	ph->last_act = THINK;
	printf("%ld\t\t%d is thinking\n", get_print_time(ph), ph->name);
	return (0);
}

static int	lock_fork(t_philo *ph)
{
	long int	last_meal;

	last_meal = get_last_meal(ph);
	pthread_mutex_lock(ph->fork[0]);
	if (get_status(ph) == -1)
	{
		pthread_mutex_unlock(ph->fork[0]);
		return (1);
	}
	else if ((get_time() - last_meal) >= ph->time_to_die)
	{
		pthread_mutex_unlock(ph->fork[0]);
		while (get_status(ph) != -1)
			usleep(25);
		return (1);
	}
	printf("%ld\t\t%d has taken a fork\n", get_print_time(ph), ph->name);
	pthread_mutex_lock(ph->fork[1]);
	if (get_status(ph) == -1)
	{
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
		return (1);
	}
	if ((get_time() - last_meal) >= ph->time_to_die)
	{
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
		while (get_status(ph) != -1)
			usleep(25);
		return (1);
	}
	printf("%ld\t\t%d has taken a fork\n", get_print_time(ph), ph->name);
	return (0);
}

static void unlock_fork(t_philo *ph)
{
	int	status;

	pthread_mutex_unlock(ph->fork[1]);
	pthread_mutex_unlock(ph->fork[0]);
	status = get_status(ph);
	if (status > 0)
	{
		printf("%ld\t\t%d has droped a fork\n", get_print_time(ph), ph->name);
		printf("%ld\t\t%d has droped a fork\n", get_print_time(ph), ph->name);
	}
}

int	eat(t_philo *ph)
{
	// pthread_t	aux;

	ph->last_act = EAT;
	if (lock_fork(ph))
		return (-1);
	printf("%ld\t\t%d is eating\n", get_print_time(ph), ph->name);
	set_last_meal(ph, get_time() + ph->time_to_eat);
	// pthread_create(&aux, NULL, &set_last_meal, &((t_set_last_meal){ph, get_time() + ph->time_to_eat}));
	// pthread_detach(aux);
	//set_last_meal(ph, get_time() + ph->time_to_eat);
	sleep_ms(ph->time_to_eat);
	unlock_fork(ph);
	if (ph->notepme-- == 0)
	{
		printf("%ld\t\t%d finish eating\n", get_print_time(ph), ph->name);
		add_status(ph, -1);
		return (1);
	}
	return (0);
}

int	philo_sleep(t_philo	*ph)
{
	ph->last_act = SLEEP;
	printf("%ld\t\t%d is sleeping\n", get_print_time(ph), ph->name);
	sleep_ms(ph->time_to_sleep);
	return (0);
}

void	*die(t_philo *ph)
{
	set_status(ph, -1);
	ph->exs->time_of_death = ph->time - ph->time_zero;
	ph->exs->status = ph->last_act;
	return ((void *)ph->exs);
}
