/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/02/22 10:49:47 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (philo->time);
}

int is_alive(t_philo *philo)
{
	get_time(philo);
	if ((philo->time - philo->last_meal) < philo->time_to_die)
		return (1);
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	while (is_alive(ph))
	{
		//printf("==========<%d>==========\n", ph->name);
		if (ph->last_act == NULL || ph->last_act == psleep)
			think(ph);
		else if (ph->last_act == think)
		{
			if (eat(ph) == -1)
				return(printf("%d died trying to eat\n", ph->phid), NULL);
		}
		else if (ph->last_act == eat)
			psleep(ph);
	}
	printf("EXIT %d\n", ph->phid);
	return (NULL);
}
