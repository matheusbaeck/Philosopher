/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:57:11 by math42            #+#    #+#             */
/*   Updated: 2023/11/21 22:09:58 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	think(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	printf("%lu %d is thinking\n", ph->time - ph->born_time, ph->name + 1);
	*(ph->status) = THK;
	return (0);
}

int	eat(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	while (*(ph->turn) == RED)
		usleep(1);
	*(ph->status) = EAT;
	if (lock_fork(ph) == -1)
		return (-1);
	get_time(ph);
	if ((ph->last_meal - ph->time) > ph->time_to_eat)
		return (-1);
	ph->last_meal = ph->time;
	printf("%ld %d is eating\n", ph->time - ph->born_time, ph->name + 1);
	pwait(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	pthread_mutex_unlock(ph->fork[1]);
	get_time(ph);
	printf("%ld %d drop fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 1);
	printf("%ld %d drop fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 2);
	*(ph->status) = 1;
	return (0);
}

int	psleep(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	*(ph->status) = SLP;
	printf("%lu %d is sleeping\n", ph->time - ph->born_time, ph->name + 1);
	pwait(ph->time_to_sleep);
	return (0);
}

int	die(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	*(ph->status) = DEAD;
	printf("%lu %d is dead\n", ph->time - ph->born_time, ph->name + 1);
	return (0);
}
