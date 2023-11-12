/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2023/09/13 12:57:16 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init(int argc, char **argv, t_data *dt)
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
			(void *) NULL, black_hole, i, 0, 0, divisor});
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
