/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/03/01 18:56:54 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	set_time(t_philo *philo)
{
	philo->time = get_time();
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
	philo->exs->time_of_death = philo->time - philo->time_zero;
	philo->exs->status = philo->last_act;
	philo->last_act = DEAD;
	return (0);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	while (ph->notepme != 0)
	{
		if (ph->last_act == UNITIALIZED || ph->last_act == SLEEP)
			think(ph);
		else if (ph->last_act == THINK)
			eat(ph);
		else if (ph->last_act == EAT)
			philo_sleep(ph);
	}
	return ((void *)ph->exs);
}
