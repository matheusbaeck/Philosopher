/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2023/12/23 16:14:09 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	update_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *) philo);
	update_time(ph);
	while ((ph->time - ph->last_meal) < ph->time_to_die)
	{
		if (*(ph->status) == NOT_INIT || *(ph->status) == SLP)
		{
			if (think(ph) == -1)
				return (NULL);
		}
		else if (*(ph->status) == THK)
		{
			if (eat(ph) == -1)
				return (NULL);
		}
		else if (*(ph->status) == EAT)
		{
			if (psleep(ph) == -1)
				return (NULL);
		}
		update_time(ph);
	}
	return (NULL);
}
