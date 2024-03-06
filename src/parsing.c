/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:54:18 by math              #+#    #+#             */
/*   Updated: 2024/03/06 18:45:29 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int check_entry(int argc, char **argv)
{
    (void)argv;
    if (argc < 5 || argc > 6)
		  return (perror("few args"), 1);
    return (0);
}