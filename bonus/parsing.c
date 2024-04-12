/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:54:18 by math              #+#    #+#             */
/*   Updated: 2024/04/10 20:18:03 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"


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

int	is_alldigit(char *str)
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
	while (((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
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

int	check_entry(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (printf("Philosopher: few args\n"), 1);
	i = 0;
	while (++i < argc)
	{
		if (!is_alldigit(argv[i]))
			return (printf("Philosopher: forbiden character\n"), 1);
		if (ft_atoi(argv[i]) <= 0)
			return (printf("Philosopher: forbiden number\n"), 1);
	}
	return (0);
}
