/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:57:11 by math42            #+#    #+#             */
/*   Updated: 2023/12/23 16:15:52 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	think(t_philo *ph)
{
	update_time(ph);
	printf("%lu %d is thinking\n", ph->time - ph->born_time, ph->name + 1);
	*(ph->status) = THK;
	return (EXIT_SUCCESS);
}

int	eat(t_philo *ph)
{
	while (*(ph->turn) != GREEN)
	{
		update_time(ph);
		if ((ph->time - ph->last_meal) > ph->time_to_die)
			return (EXIT_FAILURE);
	}
	update_time(ph);
	if (lock_fork(ph) != 0)
		return (EXIT_FAILURE);
	*(ph->status) = EAT;
	ph->i_eat++;
	update_time(ph);
	if ((ph->time - ph->last_meal) > ph->time_to_die)
		return (EXIT_FAILURE);
	ph->last_meal = ph->time;
	printf("%ld %d is eating\n", ph->time - ph->born_time, ph->name + 1);
	if ((ph->time - ph->last_meal + ph->time_to_eat) >= ph->time_to_die)
	{
		pwait(ph->time_to_die - (ph->time - ph->last_meal));
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
		return (EXIT_FAILURE);
	}
	else
		pwait(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	pthread_mutex_unlock(ph->fork[1]);
	update_time(ph);
	printf("%ld %d drop fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 1);
	printf("%ld %d drop fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 2);
	return (EXIT_SUCCESS);
}

int	psleep(t_philo *ph)
{
	update_time(ph);
	if ((ph->time - ph->last_meal) >= ph->time_to_die)
		return (EXIT_FAILURE);
	*(ph->status) = SLP;
	printf("%lu %d is sleeping\n", ph->time - ph->born_time, ph->name + 1);
	if ((ph->time - ph->last_meal + ph->time_to_sleep) >= ph->time_to_die)
	{
		pwait(ph->time_to_die - (ph->time - ph->last_meal));
		return (EXIT_FAILURE);
	}
	else
		pwait(ph->time_to_sleep);
	return (EXIT_SUCCESS);
}

int	die(t_philo *ph)
{
	if (ph->must_eat >= 0 && ph->i_eat >= ph->must_eat)
	{
		*(ph->status) = DEAD;
		return (EXIT_SUCCESS);
	}
	update_time(ph);
	printf("%lu %d is dead\n", ph->time - ph->born_time, ph->name + 1);
	*(ph->status) = DEAD;
	return (EXIT_FAILURE);
}
