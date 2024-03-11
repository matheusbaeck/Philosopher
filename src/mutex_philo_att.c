/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_philo_att.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:37:55 by math              #+#    #+#             */
/*   Updated: 2024/03/07 11:38:28 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int	get_last_meal(t_philo *self)
{
	long int	ret_val;

	pthread_mutex_lock(self->mutex_philo_att);
	ret_val = self->last_meal;
	pthread_mutex_unlock(self->mutex_philo_att);
	return (ret_val);
}

void	set_last_meal(t_philo *self, long int val)
{
	pthread_mutex_lock(self->mutex_philo_att);
	self->last_meal = val;
	pthread_mutex_unlock(self->mutex_philo_att);
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