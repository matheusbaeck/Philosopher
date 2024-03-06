/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:15:00 by math              #+#    #+#             */
/*   Updated: 2024/03/04 13:36:18 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	mutex_iter(int (*fptr)(pthread_mutex_t *), pthread_mutex_t *mutex, int size)
{
	int i;

	i = -1;
	while (++i < size)
    {
        fptr(&mutex[i]);
    }
}

void	mutex_iter_even(int (*fptr)(pthread_mutex_t *), pthread_mutex_t *mutex, int size)
{
	int i;

	i = -1;
	while (++i < size)
		if (i % 2 == 0)
			fptr(&mutex[i]);
}

void	mutex_iter_odd(int (*fptr)(pthread_mutex_t *), pthread_mutex_t *mutex, int size)
{
	int i;

	i = -1;
	while (++i < size)
		if (i % 2 == 1)
			fptr(&mutex[i]);
}