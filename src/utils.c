/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:12:41 by math42            #+#    #+#             */
/*   Updated: 2024/02/27 13:55:14 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int get_delta_time(t_philo *philo)
{
	return (get_time(philo) - philo->born_time);
}

int	sleep_ms(int mseconds)
{
	struct timeval	tv;
	long int		start_time;
	long int		delta_time;

	mseconds *= 1000;
	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	delta_time = ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
	while (delta_time < mseconds)
	{
		if ((mseconds - delta_time) / 999999 > 0)
			usleep(999999);
		else
			return (usleep((mseconds - delta_time) % 999999));
		gettimeofday(&tv, NULL);
		delta_time = ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
	}
	return (0);
}
