/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/03/05 21:39:58 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	set_time(t_philo *self)
{
	self->time = get_time();
}

long int get_delta_time(t_philo *philo)
{
	set_time(philo);
	return (philo->time - philo->time_zero);
}

int is_alive(t_philo *philo)
{
	set_time(philo);
	if ((philo->time - philo->last_meal) < philo->time_to_die)
		return (1);
	pthread_mutex_lock(philo->mutex);
	*philo->status = DEAD;
	pthread_mutex_unlock(philo->mutex);
	philo->exs->time_of_death = philo->time - philo->time_zero;
	philo->exs->status = philo->last_act;
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	while (ph->notepme != 0)
	{
		if (ph->last_act == SLEEP)
			think(ph);
		else if (ph->last_act == THINK && eat(ph) != 0)
			return ((void *)ph->exs);
		else if (ph->last_act == EAT)
			philo_sleep(ph);
	}
	return ((void *)ph->exs);
}
