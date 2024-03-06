/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/03/06 16:15:36 by mamagalh@st      ###   ########.fr       */
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
	if ((get_time() - last_meal) >= ph->time_to_die || get_status(ph) <= 0)
	{
		pthread_mutex_unlock(ph->fork[0]);
		return (1);
	}
	printf("%ld\t\t%d has taken a fork\n", get_print_time(ph), ph->name);
	pthread_mutex_lock(ph->fork[1]);
	if ((get_time() - last_meal) >= ph->time_to_die || get_status(ph) <= 0)
	{
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
		return (1);
	}
	printf("%ld\t\t%d has taken a fork\n", get_print_time(ph), ph->name);
	return (0);
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
	pthread_mutex_unlock(ph->fork[1]);
	pthread_mutex_unlock(ph->fork[0]);
	if (get_status(ph) > 0)
	{
		printf("%ld\t\t%d has droped a fork\n", get_print_time(ph), ph->name);
		printf("%ld\t\t%d has droped a fork\n", get_print_time(ph), ph->name);
	}
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

