/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:15:30 by math42            #+#    #+#             */
/*   Updated: 2023/11/16 14:42:44 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	controller_init(t_controller *controller, int n_philo)
{
	controller->n_philo = n_philo;
	controller->notepme = (int *) malloc(n_philo * sizeof(int));
	controller->traffic_control = (int *) malloc(n_philo * sizeof(int));
	controller->turn = (int *) malloc(n_philo * sizeof(int));
	controller->n_groups = 2;
	if (controller->n_philo % 2 == 1)
		controller->n_groups = 3;
}

void	set_group_turn(t_controller *controller, int j)
{
	int	i;

	i = -1;
	while (++i < (controller->n_philo - 1))
	{
		if ((i % controller->n_groups) == j)
			controller->turn[i] = GREEN;
		else
			controller->turn[i] = RED;
	}
}

void	*controller_loop(void *controller)
{
	int				i;
	int				j;
	t_controller	*con;

	con = (t_controller *) controller;
	j = -1;
	while (++j)
	{
		j = j % con->n_groups;
		i = 0;
		while (++i < (con->n_philo -1))
		{
			if (con->traffic_control[i] % con->n_groups == j
				&& con->traffic_control[i] == EAT)
				--i;
		}
		set_group_turn(con, j);
	}
	return (0);
}