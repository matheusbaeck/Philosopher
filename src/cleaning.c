/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:49:25 by math              #+#    #+#             */
/*   Updated: 2024/04/16 16:25:39 by mamagalh@st      ###   ########.fr       */
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

void	free_data_aux(t_data *dt)
{
	if (dt->last)
	{
		free(dt->last);
		dt->last = NULL;
	}
	if (dt->notepme)
	{
		free(dt->notepme);
		dt->last = NULL;
	}
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
		free(dt->mutex_philo_att);
		dt->mutex_philo_att = NULL;
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
	free_data_aux(dt);
}
