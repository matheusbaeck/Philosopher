/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:15:30 by math42            #+#    #+#             */
/*   Updated: 2023/11/22 15:28:33 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_controller(t_controller	*con)
{
	int	i;

	i = -1;
	printf("PHILO_STATUS ");
	while (++i < (con->n_philo))
	{
		printf("%d ", con->philo_status[i]);
	}
	printf("\n");
	i = -1;
	printf("TURN         ");
	while (++i < (con->n_philo))
	{
		printf("%d ", con->turn[i]);
	}
	printf("\n");
}

void	wait_philo_init(t_controller *con)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (con->philo_status[i] == NOT_INIT)
			i--;
	}
}

void	set_lights_green(t_controller *con, int j)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (con->philo_status == DEAD)
			kill_them_all(con->thread, i);
		if (con->notepme && i % con->n_groups == j && con->notepme[i] > 0)
		{
			con->turn[i] = GREEN;
			--con->notepme[i];
		}
		else if (i % con->n_groups == j)
			con->turn[i] = GREEN;	
	}
}

void	wait_start_eating(t_controller *con, int j)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (i % con->n_groups == j && con->turn[i] == GREEN)
		{
			if (con->philo_status[i] == EAT)
				con->turn[i] = RED;
			else
				i--;
		}
	}
}

void	wait_end_eating(t_controller *con, int j)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (i % con->n_groups == j && con->philo_status[i] == EAT)
		{
			i--;
		}
	}
}

int	check_notepme(t_controller *con)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (con->notepme[i] > 0)
			return (0);
	}
	return (1);
}

void	*controller_loop(void *controller)
{
	int				j;
	t_controller	*con;

	con = (t_controller *) controller;
	wait_philo_init(con);
	j = -1;
	while (++j >= 0)
	{
		j = j % con->n_groups;
		set_lights_green(con, j);
		wait_start_eating(con, j);
		wait_end_eating(con, j);
		printf("no print == no work, is C broken?\n");
		if (con->notepme && check_notepme(con))
		{
			printf("fuck!! pasta bus error :3");
			break ;
		}
	}
	return (0);
}
