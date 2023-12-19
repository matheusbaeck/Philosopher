/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:15:30 by math42            #+#    #+#             */
/*   Updated: 2023/12/19 12:28:43 by baeck            ###   ########.fr       */
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
		if (con->philo_status[i] == DEAD)
			kill_them_all(con->thread, i, con->n_philo);
		if (i % con->n_groups == j && con->turn[i] != BLUE)
		{
			if (con->notepme)
			{
				if (con->notepme[i] > 0)
				{
					con->turn[i] = GREEN;
					--con->notepme[i];
				}
				else
					con->turn[i] = BLUE;
			}
			else
				con->turn[i] = GREEN;
		}
	}
}

int	wait_start_eating(t_controller *con, int j)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (con->philo_status[i] == DEAD)
			kill_them_all(con->thread, i, con->n_philo);
		if (i % con->n_groups == j && con->turn[i] == GREEN)
		{
			if (con->philo_status[i] == EAT)
				con->turn[i] = YELLOW;
			else
				return (1);
		}
	}
	return (0);
}

int	wait_end_eating(t_controller *con, int j)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		if (con->philo_status[i] == DEAD)
			kill_them_all(con->thread, i, con->n_philo);
		if (i % con->n_groups == j && con->turn[i] == YELLOW)
		{
			if (con->philo_status[i] == EAT)
				return (1);
			else
				con->turn[i] = RED;
		}
	}
	return (0);
}

int	check_notepme(t_controller *con)
{
	int	i;

	i = -1;
	while (++i < (con->n_philo))
	{
		//printf("checking %i %i\n", i, con->notepme[i]);
		if (con->notepme[i] > 0)
			return (0);
	}
	return (1);
}

void	*controller_loop(void *controller)
{
	int				group_turn;
	t_controller	*con;

	con = (t_controller *) controller;
	wait_philo_init(con);
	group_turn = -1;
	while (++group_turn >= 0)
	{
		group_turn = group_turn % con->n_groups;
		set_lights_green(con, group_turn); //set some lights (GREEN || BLUE)
		while (wait_start_eating(con, group_turn)); //wait till all GREEN lighted ph status are EAT, set light YELLOW
		while (wait_end_eating(con, group_turn)); //wait till all YELLOW lighted ph status are not EAT, set light RED
		if (con->notepme && check_notepme(con))
		{
			printf("Ohh!! bus pasta :3\n");
			break ;
		}
	}
	return (0);
}
