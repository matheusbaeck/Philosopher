/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_philo_att.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:37:55 by math              #+#    #+#             */
/*   Updated: 2024/04/16 01:18:48 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_last_meal(t_philo *self)
{
	long int	ret_val;

	pthread_mutex_lock(self->mutex_philo_att);
	ret_val = self->last_meal;
	pthread_mutex_unlock(self->mutex_philo_att);
	return (ret_val);
}

int	set_last_meal(t_philo *self, long int val)
{
	pthread_mutex_lock(self->mutex_philo_att);
	if ((get_time() - self->last_meal) > self->time_to_die)
		return (pthread_mutex_unlock(self->mutex_philo_att), 0);
	self->last_meal = val;
	pthread_mutex_unlock(self->mutex_philo_att);
	return (1);
}

int	get_notepme(t_philo *self)
{
	int	ret_val;

	pthread_mutex_lock(self->mutex_philo_att);
	ret_val = self->notepme;
	pthread_mutex_unlock(self->mutex_philo_att);
	return (ret_val);
}

int	add_notepme(t_philo *self, int val)
{
	int	ret_val;

	pthread_mutex_lock(self->mutex_philo_att);
	self->notepme += val;
	ret_val = self->notepme;
	pthread_mutex_unlock(self->mutex_philo_att);
	return (ret_val);
}

void	get_both(t_philo *self, long int *last_meal, int *notepme)
{
	pthread_mutex_lock(self->mutex_philo_att);
	*last_meal = self->last_meal;
	*notepme = self->notepme;
	pthread_mutex_unlock(self->mutex_philo_att);
}
