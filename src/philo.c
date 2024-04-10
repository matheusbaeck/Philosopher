/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/04/10 18:37:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"


static void philo_sync(t_philo *ph)
{
	while (get_time() != ph->time_zero)
		;
	if (ph->phid % 2 == 0)
		usleep(100);
}

void	*philo_loop(void *philo)
{
	t_philo		*ph;
	int			alive;

	ph = ((t_philo *)philo);
	philo_sync(ph);
	alive = 1;
	while (alive)
	{
		if (ph->last_act == SLEEP)
			alive = think(ph);
		else if (ph->last_act == THINK)
			alive = lock_fork_one(ph);
		else if (ph->last_act == FORK_ONE)
			alive = lock_fork_two(ph);
		else if (ph->last_act == FORK_TWO)
			alive = eat(ph);
		else if (ph->last_act == EAT)
			alive = philo_sleep(ph);
	}
	return (NULL);
}
