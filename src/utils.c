/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:12:41 by math42            #+#    #+#             */
/*   Updated: 2024/04/09 16:32:02 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

// int	sleep_ms(int mseconds)
// {
// 	struct timeval	tv;
// 	long int		start_time;
// 	long int		delta_time;

// 	mseconds *= 1000;
// 	gettimeofday(&tv, NULL);
// 	start_time = tv.tv_sec * 1000000 + tv.tv_usec;
// 	delta_time = 0;
// 	while (delta_time < mseconds)
// 	{
// 		gettimeofday(&tv, NULL);
// 		delta_time = ((tv.tv_sec * 1000000 + tv.tv_usec / 1) - start_time);
// 		if ((mseconds - delta_time) > 999999)
// 			usleep(999999);
// 		else
// 			return (usleep(mseconds - delta_time));
// 	}
// 	return (0);
// }
int	sleep_ms(int mseconds)
{
    long int useconds;
    long int seconds;

    useconds = (mseconds % 1000) * 1000;
    seconds = mseconds / 1000;
    
    if (useconds > 0)
        usleep(useconds);
    if (seconds > 0)
        sleep(seconds);
	return (0);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
