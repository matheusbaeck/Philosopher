/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:54:18 by math              #+#    #+#             */
/*   Updated: 2024/03/11 20:15:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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
    return (0);
}
