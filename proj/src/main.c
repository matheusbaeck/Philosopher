/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2023/11/16 14:41:23 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init(int argc, char **argv, t_data *dt)
{
	int			i;
	int			n_philo;

	n_philo = atoi(argv[1]);
	//mutexes & threads & philos MALLOCS
	dt->fork = (pthread_mutex_t *) malloc(n_philo * sizeof(pthread_mutex_t));
	dt->routine = (pthread_t *) malloc(n_philo + 1 * sizeof(pthread_t));
	dt->philo = (t_philo *) malloc(n_philo * sizeof(t_philo));
	dt->controller = (t_controller *) malloc(n_philo * sizeof(t_controller));
	//trafic control
	controller_init(dt->controller, n_philo);
	i = -1;
	while (++i < n_philo)
	{
		dt->controller->turn[i] = 0; // std red
		dt->controller->traffic_control[i] = 0; //std red
		if (argc >= 6)
			*dt->controller->notepme = atoi(argv[i]);
		philo_init(&dt->philo[i],
			(t_philo){{
			&dt->fork[((i + n_philo) % n_philo)],
			&dt->fork[((i + n_philo + 1) % n_philo)]},
			0, 0, 0, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
			(void *) NULL, i, &dt->controller->turn[i],
			&dt->controller->traffic_control[i]});
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			dt;
	int				i;

	if (argc < 5)
		return (perror("few args"), 1);
	if (init(argc, argv, &dt))
		return (perror("init fail"), 1);
	i = -1;
	while (++i < dt.controller->n_philo)
	{
		pthread_create(&dt.routine[i], NULL, philo_loop, &dt.philo[i]);
	}
	pthread_create(&dt.routine[i], NULL, controller_loop, &dt.controller);
	i = -1;
	while (++i < dt.controller->n_philo)
	{
		pthread_join(dt.routine[i], NULL);
	}
	return (0);
}
