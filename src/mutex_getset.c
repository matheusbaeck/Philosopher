/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_getset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:54:59 by math              #+#    #+#             */
/*   Updated: 2024/03/06 17:48:27 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int	get_last_meal(t_philo *self)
{
	long int	ret_val;

	pthread_mutex_lock(self->mutex_lstmeal);
	ret_val = self->last_meal;
	pthread_mutex_unlock(self->mutex_lstmeal);
	return (ret_val);
}

void	set_last_meal(t_philo *self, long int val)
{
	pthread_mutex_lock(self->mutex_lstmeal);
	self->last_meal = val;
	pthread_mutex_unlock(self->mutex_lstmeal);
}

int	get_status(t_philo *self)
{
	int	ret_val;

	pthread_mutex_lock(self->mutex_status);
	ret_val = *self->status;
	pthread_mutex_unlock(self->mutex_status);
	return (ret_val);
}

void	set_status(t_philo *self, int val)
{
	pthread_mutex_lock(self->mutex_status);
	*self->status = val;
	pthread_mutex_unlock(self->mutex_status);
}

void	add_status(t_philo *self, int val)
{
	pthread_mutex_lock(self->mutex_status);
	*self->status += val;
	pthread_mutex_unlock(self->mutex_status);
}