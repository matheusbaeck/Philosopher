/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/04/09 18:30:57 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int	get_print_time(t_philo *self)
{
	return (get_time() - self->time_zero);
}

void	*philo_loop(void *philo)
{
	t_philo		*ph;

	ph = ((t_philo *)philo);
	while (get_status(ph) > 0)
	{
		think(ph);
		if (eat(ph))
			return (NULL);
		philo_sleep(ph);
	}
	return (NULL);
}
