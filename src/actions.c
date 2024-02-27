/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/02/27 18:40:27 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	think(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	printf("%lu %d is thinking\n", get_delta_time(ph), ph->name);
	ph->last_act = think;
	return (0);
}

static int	take_fork(t_philo *ph)
{
	while (pthread_mutex_lock(ph->fork[0]))
	{
		if (!is_alive(ph))
			return (pthread_mutex_unlock(ph->fork[0]), -1);
	}
	printf("%ld %d took fork\n", get_delta_time(ph), ph->name);
	while (pthread_mutex_lock(ph->fork[1]))
	{
		if (!is_alive(ph))
			return (pthread_mutex_unlock(ph->fork[0]), pthread_mutex_unlock(ph->fork[1]), -1);
	}
	printf("%ld %d took fork\n", get_delta_time(ph), ph->name);
	return (0);
}

int	eat(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	if (take_fork(ph))
		return (-1);
	ph->last_act = eat;
	ph->last_meal = ph->time;
	printf("%ld %d is eating\n", get_delta_time(ph), ph->name);
	sleep_ms(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	printf("%ld %d droped fork\n", get_delta_time(ph), ph->name);
	pthread_mutex_unlock(ph->fork[1]);
	printf("%ld %d droped fork\n", get_delta_time(ph), ph->name);
	if (ph->notepme-- == 0)
	{
		printf("%ld %d end eating\n", get_delta_time(ph), ph->name);
		return (1);
	}
	return (0);
}

int	psleep(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	ph->last_act = psleep;
	printf("%lu %d is sleeping\n", get_delta_time(ph), ph->name);
	sleep_ms(ph->time_to_sleep);
	return (0);
}

void	*die(void *philo, int status)
{
	t_philo	*ph;
	t_philo_exit *exs;

	ph = ((t_philo *)philo);
	exs = malloc(sizeof(t_philo_exit));
	exs->phid = ph->phid;
	exs->status = status;
	exs->last_act = ph->last_act;
	if (status == -1)
		printf("%lu %d is dead\n", get_delta_time(ph), ph->name);
	return ((void *)exs);
}
