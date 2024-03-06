/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/03/06 12:16:10 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	set_time(t_philo *self)
{
	self->time = get_time();
}

long int get_print_time(t_philo *self)
{
	set_time(self);
	return (self->time - self->time_zero);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);
	while (get_status(ph) > 0)
	{
		if (ph->last_act == SLEEP)
			think(ph);
		else if (ph->last_act == THINK)
		{
			if (eat(ph) != 0)
				return (die(ph));
		}
		else if (ph->last_act == EAT)
			philo_sleep(ph);
	}
	return (die(ph));
}
