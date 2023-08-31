/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2023/08/31 02:37:33 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_init(t_philo *dest, t_philo philo)
{
	*dest = philo;
	get_time(dest);
	dest->born_time = dest->time;
	dest->last_meal = dest->time;
}

int	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = tv.tv_usec;
	return (0);
}

int	set_forks(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < dt->n_philo)
	{
		dt->philo[i].fork[0] = dt->fork[((i + dt->n_philo - 1) % dt->n_philo)];
	}
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;
	int		i;

	ph = ((t_philo *)philo);
	get_time(ph);
	while ((ph->time - ph->last_meal) < ph->time_to_die)
	{
		if (ph->last_act == NULL || ph->last_act == psleep)
			think(ph);
		else if (ph->last_act == think)
		{
			i = 1;
			while (i != 0)
			{
				i = eat(ph);
				if (i == 1)
					usleep(ph->time_to_eat);
				else
					return (printf("%d died\n, ", ph->name), NULL);
			}
		}
		else if (ph->last_act == eat)
			psleep(ph);
	}
	printf("EXIT\n");
	return (NULL);
}
