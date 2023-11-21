/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:12:41 by math42            #+#    #+#             */
/*   Updated: 2023/11/21 23:04:38 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	lock_fork(t_philo *philo)
{
	int	e;

	get_time(philo);
	if ((philo->time - philo->last_meal) < philo->time_to_die)
	{
		e = pthread_mutex_lock(philo->fork[0]);
		printf("%ld %d took fork %d\n",
			philo->time - philo->born_time, philo->name + 1, philo->name + 1);
		if (e != 0)
			return (printf("error locking\n"), e);
		e = pthread_mutex_lock(philo->fork[1]);
		printf("%ld %d took fork %d\n", 
			philo->time - philo->born_time, philo->name + 1, philo->name + 2);
		if (e != 0)
			return (printf("error locking\n"), e);
		return (0);
	}
	return (-1);
}

int	pwait(int mseconds)
{
	struct timeval	tv;
	long int		start_time;
	long int		delta_time;

	mseconds *= 1000;
	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	delta_time = ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
	while (delta_time < mseconds)
	{
		if ((mseconds - delta_time) / 999999 > 0)
			usleep(999999);
		else
			return (usleep((mseconds - delta_time) % 999999));
		gettimeofday(&tv, NULL);
		delta_time = ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
	}
	return (0);
}
