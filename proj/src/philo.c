/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2023/11/21 23:22:49 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

int	set_forks(t_data *dt, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_mutex_init(&dt->fork[i], NULL))
			printf("fork %d fail at %p\n", i, &dt->fork[i]);
	}
	i = -1;
	while (++ i < n_philo)
	{
		dt->philo[i].fork[0] = &dt->fork[((i + n_philo) % n_philo)];
		dt->philo[i].fork[1] = &dt->fork[((i + n_philo + 1) % n_philo)];
	}
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	get_time(ph);
	while ((ph->time - ph->last_meal) < ph->time_to_die)
	{
		if (*(ph->status) == NOT_INIT || *(ph->status) == SLP)
			think(ph);
		else if (*(ph->status) == THK)
		{
			if (eat(ph) == -1)
				return (die(ph), NULL);
		}
		else if (*(ph->status) == EAT)
			psleep(ph);
		get_time(ph);
	}
	die(ph);
	return (NULL);
}
