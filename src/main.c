/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/04/16 14:57:52 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int any_need_eat(int *arr, int size)
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

static int	is_dead(t_data *dt, long int *last, int *notepme, int i)
{
	int 	temp_notepme;

	if (notepme[i] == 0)
		return (0);
	if (((get_time() - *last) <= dt->time_to_die))
		return (0);
	get_both(&dt->philo[i], last, &temp_notepme);
	if (temp_notepme == 0)
		notepme[i] = 0;
	if (((get_time() - *last) > dt->time_to_die) && notepme[i] != 0)
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
	int			notepme[dt->n_philo];
	long int	last[dt->n_philo];

	time = get_time();
	i = -1;
	while (++i < dt->n_philo)
	{
		notepme[i] = 1;
		last[i] = 0;
	}
	while (any_need_eat(notepme, dt->n_philo))
	{
		while ((get_time() - time) < (long int)(5))
			usleep(100);
		time = get_time();
		i = -1;
		while (++i < dt->n_philo)
		{
			if (is_dead(dt, &(last[i]), &(*notepme), i))
				return ;
		}
	}
	printf("FINIDH\n");
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
