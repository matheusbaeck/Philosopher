/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2023/09/13 12:11:45 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	think(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	printf("%lu %d is thinking\n", ph->time - ph->born_time, ph->name +1);
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
	printf("%ld %d is eating\n", ph->time - ph->born_time, ph->name + 1);
	pwait(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	get_time(ph);
	printf("%ld %d droped fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name);
	pthread_mutex_unlock(ph->fork[1]);
	printf("%ld %d droped fork %d\n", ph->time - ph->born_time, ph->name + 1, ph->name + 2);
	return (0);
}

int	psleep(void *philo)
{
	t_philo	*ph;
	int		i;

	ph = ((t_philo *)philo);
	get_time(ph);
	ph->last_act = psleep;
	printf("%lu %d is sleeping\n", ph->time - ph->born_time, ph->name + 1);
	i = -1;
	while(++i < ph->time_to_sleep)
		pwait(ph->time_to_sleep);
	return (0);
}

int	die(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	ph->last_act = die;
	printf("%lu %d is dead\n", ph->time - ph->born_time, ph->name + 1);
	return (0);
}
