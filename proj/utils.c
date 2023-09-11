/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:12:41 by math42            #+#    #+#             */
/*   Updated: 2023/09/12 01:43:44 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	try_lock(t_philo *philo)
{
	int	d;
	int	e;

	d = 3;
	while (!get_time(philo) && (philo->time - philo->last_meal) < philo->time_to_die)
	{
		if (((philo->time % (philo->time_to_eat * d)) / philo->time_to_eat) == (philo->name % d))
		{
			//printf("%d action\n forks %p and %p\n", philo->name, &philo->fork[0], &philo->fork[1]);
			e = pthread_mutex_lock(&philo->fork[0]);
			//printf("%i\n", e);
			if (e == 0)
			{
				//printf(" locked %p\n", &philo->fork[0]);
				e = pthread_mutex_lock(&philo->fork[1]);
				if (e == 0)
					return (0); // printf(" locked %p\n SUCESS\n", &philo->fork[1]), 
				else
				{
					pthread_mutex_unlock(&philo->fork[0]);
					//printf(" fail locking %p    %d\n", &philo->fork[1], e);
					// if (pthread_mutex_unlock(&philo->fork[0]) == 0)
					// 	printf(" unlocking\n");
					// else
					// 	printf(" fail unlocking");
				}
			}
			// else
			// {
			// 	//printf(" fail locking %p    %d\n", &philo->fork[0], e);
			// 	pwait(1);
			// }
			// usleep(4 * 100 * 1000);
		}
		// else
		// {
		// 	pwait(1);
		// }
	}
	return (-1);
}

//current_time() - philo->start_time - philo->last_meal > philo->time_to_die

int	try_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork[0]);
	pthread_mutex_unlock(&philo->fork[1]);
	// if (!pthread_mutex_unlock(&philo->fork[0]))
	// 	printf(" unlocked %p\n", &philo->fork[0]);
	// else
	// 	printf(" fail unlocking %p\n", &philo->fork[0]);
	// if (!pthread_mutex_unlock(&philo->fork[1]))
	// 	printf(" unlocked %p\n", &philo->fork[1]);
	// else
	// 	printf(" fail unlocking %p\n", &philo->fork[1]);
	return (0);
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
