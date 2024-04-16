/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/04/16 16:27:06 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	any_need_eat(int *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (arr[i] != 0)
			return (1);
	}
	return (0);
}

static int	is_dead(t_data *dt, int i)
{
	if (dt->notepme[i] == 0)
		return (0);
	if (((get_time() - dt->last[i]) <= dt->time_to_die))
		return (0);
	get_both(&dt->philo[i], &(dt->last[i]), &(dt->notepme[i]));
	if (((get_time() - dt->last[i]) > dt->time_to_die) && dt->notepme[i] != 0)
	{
		set_status(&dt->philo[i], -1);
		printf("%ld\t%d is dead\n", get_time() - dt->time_zero, i + 1);
		return (1);
	}
	return (0);
}

static void	cheker(t_data *dt)
{
	int			i;
	long int	time;

	time = get_time();
	i = -1;
	while (++i < dt->n_philo)
	{
		dt->notepme[i] = 1;
		dt->last[i] = 0;
	}
	while (any_need_eat(dt->notepme, dt->n_philo))
	{
		while ((get_time() - time) < (long int)(5))
			usleep(100);
		time = get_time();
		i = -1;
		while (++i < dt->n_philo)
		{
			if (is_dead(dt, i))
				return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	dt;
	int		i;

	if (check_entry(argc, argv))
		return (1);
	if (init(argc, argv, &dt))
		return (free_data(&dt), 1);
	i = -1;
	while (++i < dt.n_philo)
	{
		if (pthread_create(&dt.routine[i], NULL, philo_loop, &dt.philo[i]) != 0)
			perror("pthread_create");
	}
	cheker(&dt);
	i = -1;
	while (++i < dt.n_philo)
		pthread_join(dt.routine[i], NULL);
	destroy_mutex(&dt);
	free_data(&dt);
	return (0);
}
