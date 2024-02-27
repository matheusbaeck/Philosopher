/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/02/22 03:40:56 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philo_init(t_philo *dest, t_philo philo)
{
	*dest = philo;
	get_time(dest);
	dest->born_time = dest->time;
	dest->last_meal = dest->time;
}

static int	init(int argc, char **argv, t_data *dt)
{
	int			i;
	int 		divisor;
	long long	black_hole;

	dt->n_philo = atoi(argv[1]);
	dt->time_to_die = atoi(argv[2]);
	dt->time_to_eat = atoi(argv[3]);
	dt->time_to_sleep = atoi(argv[4]);
	divisor = 2;
	if (dt->n_philo % 2 == 1)
		divisor = 3;
	i = -1;
	while (++i < dt->n_philo)
	{
		black_hole = -1;
		if (argc >= 6)
			black_hole = atoi(argv[i]);
		philo_init(&dt->philo[i],
			(t_philo){{0, 0},
			0, dt->time_to_die, dt->time_to_eat, dt->time_to_sleep,
			(void *) NULL, black_hole, i, i + 1, 0, 0, divisor});
	}
	return (0);
}

static int	set_forks(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < dt->n_philo)
	{
		if (pthread_mutex_init(&dt->fork[i], NULL))
			printf("fork %d fail at %p\n", i, &dt->fork[i]);
	}
	i = -1;
	while (++ i < dt->n_philo)
	{
		if (i % 2 == 0)
		{
			dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo - 1) % dt->n_philo)];
			dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
		}
		else
		{
			dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo - 1) % dt->n_philo)];
			dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		dt;
	int			i;

	if (argc < 5)
		return (perror("few args"), 1);
	if (init(argc, argv, &dt) != 0)
		return (perror("init fail"), 1);
	set_forks(&dt);
	i = -1;
	while (++i < dt.n_philo)
	{
		pthread_create(&dt.routine[i], NULL, philo_loop, &dt.philo[i]);
	}
	i = -1;
	while (++i < dt.n_philo)
	{
		pthread_join(dt.routine[i], NULL);
	}
	return (0);
}
