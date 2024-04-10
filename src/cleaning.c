/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:49:25 by math              #+#    #+#             */
/*   Updated: 2024/04/10 18:45:43 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	destroy_mutex_array(pthread_mutex_t *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_mutex_destroy(&arr[i]);
}

void	destroy_mutex(t_data *dt)
{
	if (dt->fork)
		destroy_mutex_array(dt->fork, dt->n_philo);
	if (dt->mutex_philo_att)
		destroy_mutex_array(dt->mutex_philo_att, dt->n_philo);
	pthread_mutex_destroy(&dt->mutex_status);
}

void	free_data(t_data *dt)
{
	if (dt->fork)
	{
		free(dt->fork);
		dt->fork = NULL;
	}
	if (dt->mutex_philo_att)
	{
		free(dt->fork);
		dt->fork = NULL;
	}
	if (dt->routine)
	{
		free(dt->routine);
		dt->routine = NULL;
	}
	if (dt->philo)
	{
		free(dt->philo);
		dt->philo = NULL;
	}
}