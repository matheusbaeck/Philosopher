/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:54:59 by math              #+#    #+#             */
/*   Updated: 2024/04/09 13:42:29 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	print_safe(char *str, t_philo *self)
{
	pthread_mutex_lock(self->mutex_print);
	if (*self->status > 0)
		printf(str, get_print_time(self), self->name);
	pthread_mutex_unlock(self->mutex_print);
}

int	get_status(t_philo *self)
{
	int	ret_val;

	pthread_mutex_lock(self->mutex_status);
	ret_val = *self->status;
	pthread_mutex_unlock(self->mutex_status);
	return (ret_val);
}

int	set_status(t_philo *self, int val)
{
	pthread_mutex_lock(self->mutex_status);
	if (*self->status == val)
	{
		pthread_mutex_unlock(self->mutex_status);
		return (1);
	}
	*self->status = val;
	pthread_mutex_unlock(self->mutex_status);
	return (0);
}

void	add_status(t_philo *self, int val)
{
	pthread_mutex_lock(self->mutex_status);
	*self->status += val;
	pthread_mutex_unlock(self->mutex_status);
}
