/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2023/08/31 21:31:10 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	think(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	printf("%d %lu is thinking\n", ph->name, ph->time);
	ph->last_act = think;
	return (0);
}

int	eat(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	if (try_lock(ph) == -1)
		return (-1);
	get_time(ph);
	if ((ph->last_meal - ph->time) > ph->time_to_eat)
		return(-1);
	ph->last_act = eat;
	ph->last_meal = ph->time;
	printf("%d %ld is eating\n", ph->name, ph->time);
	usleep(ph->time_to_eat * 1000 * 1000);
	try_unlock(ph);
	return (0);
}

int	psleep(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	ph->last_act = psleep;
	printf("%d %lu is sleeping\n", ph->name, ph->time);
	usleep(ph->time_to_sleep * 1000 * 1000);
	return (0);
}

int	die(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	ph->last_act = die;
	printf("%d %lu is dead\n", ph->name, ph->time);
	return (0);
}
