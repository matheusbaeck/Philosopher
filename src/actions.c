/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/03/11 19:08:34 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	think(t_philo *ph)
{
	ph->last_act = THINK;
	print_safe("%ld\t\t%d is thinking\n", ph);
	return (0);
}

static int	lock_fork_one(t_philo *ph, long int last_meal)
{
	pthread_mutex_lock(ph->fork[0]);
	if ((get_time() - last_meal) >= ph->time_to_die)
	{
		if (!set_status(ph, -1))
			printf("%ld\t%d is DEAD\n", get_print_time(ph), ph->name);
	}
	if (get_status(ph) <= 0)
	{
		pthread_mutex_unlock(ph->fork[0]);
		return (1);
	}
	print_safe("%ld\t\t%d has taken a fork\n", ph);
	if (ph->fork[0] == ph->fork[1])
	{
		sleep_ms(ph->time_to_die);
		pthread_mutex_unlock(ph->fork[0]);
		return (1);
	}
	return (0);
}

static int	lock_fork_two(t_philo *ph, long int last_meal)
{
	pthread_mutex_lock(ph->fork[1]);
	if ((get_time() - last_meal) >= ph->time_to_die)
	{
		if (!set_status(ph, -1))
			printf("%ld\t%d is DEAD\n", get_print_time(ph), ph->name);
	}
	if ((get_time() - last_meal) >= ph->time_to_die || get_status(ph) <= 0)
	{
		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);
		return (1);
	}
	print_safe("%ld\t\t%d has taken a fork\n", ph);
	return (0);
}

int	eat(t_philo *ph)
{
	long int	last_meal;

	last_meal = get_last_meal(ph);
	ph->last_act = EAT;
	if (lock_fork_one(ph, last_meal))
		return (-1);
	if (lock_fork_two(ph, last_meal))
		return (-1);
	set_last_meal(ph, get_time() + ph->time_to_eat);
	print_safe("%ld\t\t%d is eating\n", ph);
	sleep_ms(ph->time_to_eat);
	pthread_mutex_unlock(ph->fork[1]);
	pthread_mutex_unlock(ph->fork[0]);
	if (get_status(ph) > 0)
	{
		print_safe("%ld\t\t%d has droped a fork\n", ph);
		print_safe("%ld\t\t%d has droped a fork\n", ph);
	}
	if (add_notepme(ph, -1) == 0)
	{
		print_safe("%ld\t\t%d finish eating\n", ph);
		return (2);
	}
	return (0);
}

int	philo_sleep(t_philo	*ph)
{
	ph->last_act = SLEEP;
	print_safe("%ld\t\t%d is sleeping\n", ph);
	sleep_ms(ph->time_to_sleep);
	return (0);
}

