/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:54:18 by math              #+#    #+#             */
/*   Updated: 2024/03/11 18:41:21 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static int  check_notepme(char **argv)
{
    int i;
    int size;
    int count;

    i = -1;
    count = 0;
    size = ft_strlen(argv[5]);
    while (++i < size)
    {
        while (argv[5][i] == ' ')
            ++i;
        if (ft_isdigit(argv[5][i]))
            count++;
        while (ft_isdigit(argv[5][i]))
            ++i;
        argv[5][i] = '\0';
    }
    if (count != ft_atoi(argv[1]))
        return (printf("Philosopher: wrong notepme: %d philos %d args\n", ft_atoi(argv[1]), count), 1);
    return (0);
}

int check_entry(int argc, char **argv)
{
    int i;

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
    if (argc == 6 && check_notepme(argv))
    {
        return (1);
    } 
    return (0);
}
