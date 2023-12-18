/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:57:11 by math42            #+#    #+#             */
/*   Updated: 2023/11/22 15:35:47 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	think(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	update_time(ph);
	printf("%lu %d is thinking\n", ph->time - ph->born_time, ph->name + 1);
	*(ph->status) = THK;
	return (0);
}

int	eat(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	while (*(ph->turn) == RED)
	{
		update_time(ph);
		if ((ph->time - ph->last_meal) > ph->time_to_die)
			return (-1);
	}
	*(ph->status) = EAT;
	if (lock_fork(ph) != 0)
		return (-1);
	update_time(ph);
	if ((ph->time - ph->last_meal) > ph->time_to_die)
		return (-1);
	ph->last_meal = ph->time;
	printf("%ld %d is eating\n", ph->time - ph->born_time, ph->name + 1);
	pwait(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	pthread_mutex_unlock(ph->fork[1]);
	update_time(ph);
	printf("%ld %d drop fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 1);
	printf("%ld %d drop fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 2);
	return (0);
}

int	psleep(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	update_time(ph);
	if ((ph->time - ph->last_meal) >= ph->time_to_die)
		die(ph);
	printf("%lu %d is sleeping\n", ph->time - ph->born_time, ph->name + 1);
	*(ph->status) = SLP;
	if ((ph->time - ph->last_meal + ph->time_to_sleep) >= ph->time_to_die)
	{
		pwait(ph->time_to_die - (ph->time - ph->last_meal));
		die(ph);
	}
	else
		pwait(ph->time_to_sleep);
	return (0);
}

int	die(void *philo)
{
	t_philo	*ph;
	int		last_status;

	ph = ((t_philo *)philo);
	update_time(ph);
	last_status = *(ph->status);
	*(ph->status) = DEAD;
	printf("%lu %d is dead\n", ph->time - ph->born_time, ph->name + 1);
	return (last_status);
}
