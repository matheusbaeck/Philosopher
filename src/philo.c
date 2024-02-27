/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/02/27 18:45:20 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
	int		status;

	ph = ((t_philo *)philo);
	while (is_alive(ph))
	{
		//printf("==========<%d>==========\n", ph->name);
		if (ph->last_act == NULL || ph->last_act == psleep)
			think(ph);
		else if (ph->last_act == think)
		{
			status = eat(ph);
			if (status != 0)
				return (die(ph, status));
		}
		else if (ph->last_act == eat)
			psleep(ph);
	}
	return (die(ph, -1));
}
