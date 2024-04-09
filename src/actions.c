/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/04/09 18:28:51 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	think(t_philo *ph)
{
	print_safe("%ld\t\t%d is thinking\n", ph);
	return (0);
}

static int	lock_fork(t_philo *ph)
{
	pthread_mutex_lock(ph->fork[0]);
	print_safe("%ld\t\t%d has taken a fork\n", ph);
	if (ph->fork[0] == ph->fork[1])
	{
		sleep_ms(ph->time_to_die);
		pthread_mutex_unlock(ph->fork[0]);
		return (1);
	}
	pthread_mutex_lock(ph->fork[1]);
	print_safe("%ld\t\t%d has taken a fork\n", ph);
	return (0);
}

int	eat(t_philo *ph)
{
	if (lock_fork(ph))
		return (-1);
	if (set_last_meal(ph, get_time()))
		return (pthread_mutex_unlock(ph->fork[0]),
			pthread_mutex_unlock(ph->fork[1]), -1);
	print_safe("%ld\t\t%d is eating\n", ph);
	sleep_ms(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	pthread_mutex_unlock(ph->fork[1]);
	if (add_notepme(ph, -1) == 0)
		return (2);
	return (0);
}

int	philo_sleep(t_philo *ph)
{
	print_safe("%ld\t\t%d is sleeping for\n", ph);
	sleep_ms(ph->time_to_sleep);
	return (0);
}
