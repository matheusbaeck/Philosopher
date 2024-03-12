/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/03/12 17:26:32 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int	get_print_time(t_philo *self)
{
	return (get_time() - self->time_zero);
}

void	*philo_loop(void *philo)
{
	t_philo	*ph;
	int		ret;

	ph = ((t_philo *)philo);
	while (get_status(ph) > 0)
	{
		if (ph->last_act == SLEEP)
			think(ph);
		else if (ph->last_act == THINK)
		{
			ret = eat(ph);
			if (ret == 1)
				return (set_status(ph, -1), NULL);
			else if (ret == 2)
				return (add_status(ph, -1), NULL);
			else
				continue ;
		}
		else if (ph->last_act == EAT)
			philo_sleep(ph);
	}
	return (set_status(ph, -1), NULL);
}
