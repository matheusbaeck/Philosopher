/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:12:41 by math42            #+#    #+#             */
/*   Updated: 2024/03/11 18:41:21 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	sleep_ms(int mseconds)
{
	struct timeval	tv;
	long int		start_time;
	long int		delta_time;

	mseconds *= 1000;
	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000000 + tv.tv_usec;
	delta_time = 0;
	while (delta_time < mseconds)
	{
		gettimeofday(&tv, NULL);
		delta_time = ((tv.tv_sec * 1000000 + tv.tv_usec / 1) - start_time);
		if ((mseconds - delta_time) > 999999)
			usleep(999999);
		else
			return (usleep(mseconds - delta_time));
	}
	return (0);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_alldigit(char *str)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (!(ft_isdigit(str[i]) || str[i] == ' '))
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;
	int	index;

	index = 0;
	sign = 1;
	num = 0;
	while (((str[index] >= 9 && str[index] <= 13)
			|| str[index] == 32)
		&& str[index])
		index++;
	if (str[index] == '+')
		index++;
	else if (str[index] == '-')
	{
		sign *= -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		num *= 10;
		num += (str[index] - '0');
		index++;
	}
	return (num * sign);
}