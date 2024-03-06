/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:54:18 by math              #+#    #+#             */
/*   Updated: 2024/03/06 22:34:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int check_entry(int argc, char **argv)
{
    int i;
    int size;
    int count;

    if (argc < 5 || argc > 6)
		  return (printf("Philosopher: few args\n"), 1);
    i = 0;
    while (++i < argc)
    {
        if (!is_alldigit(argv[i]))
            return (printf("Philosopher: forbiden character\n"), 1);
    }
    if (argc == 6)
    {
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
    } 
    return (0);
}
