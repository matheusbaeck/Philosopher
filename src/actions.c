/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/03/01 19:03:12 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	think(t_philo *ph)
{
	ph->last_act = THINK;
	printf("%ld\t\t%d is thinking\n", get_delta_time(ph), ph->name);
	return (0);
}

int	eat(t_philo *ph)
{
	ph->last_act = EAT;
	pthread_mutex_lock(ph->fork[0]);
	printf("%ld\t\t%d has taken a fork\n", get_delta_time(ph), ph->name);
	pthread_mutex_lock(ph->fork[1]);
	printf("%ld\t\t%d has taken a fork\n", get_delta_time(ph), ph->name);
	ph->last_meal = ph->time + ph->time_to_eat;
	printf("%ld\t\t%d is eating\n", get_delta_time(ph), ph->name);
	sleep_ms(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[1]);
	printf("%ld\t\t%d has droped a fork\n", get_delta_time(ph), ph->name);
	pthread_mutex_unlock(ph->fork[0]);
	printf("%ld\t\t%d has droped a fork\n", get_delta_time(ph), ph->name);
	if (ph->notepme-- == 0)
	{
		printf("%ld\t\t%d end eating\n", get_delta_time(ph), ph->name);
		return (1);
	}
	return (0);
}

int	philo_sleep(t_philo	*ph)
{
	ph->last_act = SLEEP;
	printf("%ld\t\t%d is sleeping\n", get_delta_time(ph), ph->name);
	sleep_ms(ph->time_to_sleep);
	return (0);
}

void	*die(t_philo *ph)
{
	return ((void *)ph->exs);
}
