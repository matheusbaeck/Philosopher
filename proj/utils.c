/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:12:41 by math42            #+#    #+#             */
/*   Updated: 2023/08/31 21:34:01 by math42           ###   ########.fr       */
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
			printf("%d action\n forks %p and %p\n", philo->name, &philo->fork[0], &philo->fork[1]);
			e = pthread_mutex_lock(&philo->fork[0]);
			if (e == 0)
			{
				printf(" locked %p\n", &philo->fork[0]);
				e = pthread_mutex_lock(&philo->fork[1]);
				if (e == 0)
					return (printf(" locked %p\n SUCESS\n", &philo->fork[1]), 0);
				else
				{
					printf(" fail locking %p    %d\n", &philo->fork[1], e);
					if (pthread_mutex_unlock(&philo->fork[0]) == 0)
						printf(" unlocking\n");
					else
						printf(" fail unlocking");
				}
			}
			else
			{
				printf(" fail locking %p    %d\n", &philo->fork[0], e);
				usleep(1000 * 1000);
			}
		}
		else
		{
			usleep(1000 * 1000);
		}
	}
	return (-1);
}

int	try_unlock(t_philo *philo)
{
	if (!pthread_mutex_unlock(&philo->fork[0]))
		printf(" unlocked %p\n", &philo->fork[0]);
	else
		printf(" fail unlocking %p\n", &philo->fork[0]);
	if (!pthread_mutex_unlock(&philo->fork[1]))
		printf(" unlocked %p\n", &philo->fork[1]);
	else
		printf(" fail unlocking %p\n", &philo->fork[1]);
	return (0);
}
