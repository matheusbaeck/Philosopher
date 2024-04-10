/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2024/04/10 13:19:00 by math             ###   ########.fr       */
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
	bool		dead;

	ph = ((t_philo *)philo);
	while (get_time() != ph->time_zero)
		;
	if (ph->phid % 2 == 0)
		usleep(100);
	dead = 0;
	while (get_status(ph) > 0)
	{
		think(ph);
		if (eat(ph))
			return (NULL);
		philo_sleep(ph);
	}
	printf("JUST WAITING TO BE KILD ##############################################\n");
	return (NULL);
}
