/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2023/09/11 22:24:07 by mamagalh@st      ###   ########.fr       */
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
	philo->time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

int	set_forks(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < dt->n_philo)
	{
		if (!pthread_mutex_init(&dt->fork[i], NULL))
			printf("fork %d init at %p\n", i, &dt->fork[i]);
		else
			printf("fork %d fail at %p\n", i, &dt->fork[i]);
	}
	i = -1;
	while (++ i < dt->n_philo)
	{
		dt->philo[i].fork[0] = dt->fork[((i + dt->n_philo - 1) % dt->n_philo)];
		dt->philo[i].fork[1] = dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
		printf("%d takes fork %d and %d\n", i, (i + dt->n_philo - 1) % dt->n_philo, (i + dt->n_philo + 1) % dt->n_philo);
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
		if (ph->last_act == NULL || ph->last_act == psleep)
			think(ph);
		else if (ph->last_act == think)
		{
			if (eat(ph) == -1)
				return(printf("%d died trying to eat\n", ph->name), NULL);
		}
		else if (ph->last_act == eat)
			psleep(ph);
		get_time(ph);
	}
	printf("EXIT %d\n", ph->name);
	return (NULL);
}
