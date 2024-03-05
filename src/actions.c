/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:26 by math42            #+#    #+#             */
/*   Updated: 2024/03/05 21:58:34 by mamagalh@st      ###   ########.fr       */
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
	if (!is_alive(ph))
		return (pthread_mutex_unlock(ph->fork[0]), printf("%ld\t\t%d has droped a fork\n", get_delta_time(ph), ph->name),
				pthread_mutex_unlock(ph->fork[1]), printf("%ld\t\t%d has droped a fork\n", get_delta_time(ph), ph->name), -1);
	
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
	// int	time_left;

	// pthread_mutex_lock(&ph->mutex);
	// time_left = (ph->time - ph->last_meal) < ph->time_to_die;
	// pthread_mutex_lock(&ph->mutex);
	// ph->last_act = SLEEP;
	// printf("%ld\t\t%d is sleeping\n", get_delta_time(ph), ph->name);
	// if (time_left > ph->time_to_sleep)
	// 	sleep_ms(time_left);
	// else
	// 	sleep_ms(ph->time_to_sleep);
	ph->last_act = SLEEP;
	printf("%ld\t\t%d is sleeping\n", get_delta_time(ph), ph->name);
	sleep_ms(ph->time_to_sleep);
	return (0);
}

void	*die(t_philo *ph)
{
	return ((void *)ph->exs);
}
