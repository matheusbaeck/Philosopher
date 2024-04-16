/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/04/16 15:03:42 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	think(t_philo *ph)
{
	ph->last_act = THINK;
	return (print_safe("%ld\t\t%d is thinking\n", ph));
}

int	lock_fork_one(t_philo *ph)
{
	int	ret;

	ph->last_act = FORK_ONE;
	pthread_mutex_lock(ph->fork[0]);
	ret = print_safe("%ld\t\t%d has taken a fork\n", ph);
	if (ph->fork[0] == ph->fork[1])
	{
		sleep_ms(ph->time_to_die);
		pthread_mutex_unlock(ph->fork[0]);
		return (0);
	}
	if (ret == 0)
	{
		pthread_mutex_unlock(ph->fork[0]);
	}
	return (ret);
}

int	lock_fork_two(t_philo *ph)
{
	int	ret;

	ph->last_act = FORK_TWO;
	pthread_mutex_lock(ph->fork[1]);
	ret = print_safe("%ld\t\t%d has taken a fork\n", ph);
	if (ret == 0)
	{
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
	}
	return (ret);
}

int	eat(t_philo *ph)
{
	ph->last_act = EAT;
	if (!set_last_meal(ph, get_time()))
	{
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
		return (0);
	}
	print_safe("%ld\t\t%d is eating\n", ph);
	sleep_ms(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[0]);
	pthread_mutex_unlock(ph->fork[1]);
	if (add_notepme(ph, -1) == 0)
		return (0);
	return (1);
}

int	philo_sleep(t_philo *ph)
{
	ph->last_act = SLEEP;
	if (print_safe("%ld\t\t%d is sleeping\n", ph))
		return (sleep_ms(ph->time_to_sleep), 1);
	return (0);
}
