/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2023/08/31 02:37:14 by math42           ###   ########.fr       */
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
	if (!pthread_mutex_lock(&ph->fork[0]))
	{
		if (pthread_mutex_lock(&ph->fork[1]))
			return(pthread_mutex_unlock(&ph->fork[0]), 1);
	}
	get_time(ph);
	if ((ph->last_meal - ph->time) > ph->time_to_eat)
	{
		printf("died prematurly\n");
		return(-1);
	}
	ph->last_act = eat;
	ph->last_meal = ph->time;
	printf("%d %ld is eating\n", ph->name, ph->time);
	usleep(ph->time_to_eat);
	printf("end eating\n");
	pthread_mutex_unlock(&ph->fork[0]);
	pthread_mutex_unlock(&ph->fork[1]);
	return (0);
}

int	psleep(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	ph->last_act = psleep;
	printf("%d %lu is sleeping\n", ph->name, ph->time);
	usleep(ph->time_to_sleep);
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
