/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/03/07 11:12:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int get_print_time(t_philo *self)
{
	return (get_time() - self->time_zero);
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
			switch (eat(ph))
			{
			case 1:
				return (set_status(ph, -1), NULL);
			
			case 2:
				return (add_status(ph, -1), NULL);
			
			default:
				break;
			}
			
		}
		else if (ph->last_act == EAT)
			philo_sleep(ph);
	}
	return (set_status(ph, -1), NULL);
}
