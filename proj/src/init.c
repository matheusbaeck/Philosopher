/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:55:22 by math42            #+#    #+#             */
/*   Updated: 2023/12/26 13:46:30 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	philo_init(t_philo *philo, t_philo param, int *must_eat, int i)
{
	*philo = param;

	pthread_mutex_init(philo->fork[0], NULL);
	*(philo->status) = NOT_INIT;
	update_time(philo);
	philo->born_time = philo->time;
	philo->last_meal = philo->time;
	if (must_eat)
		philo->must_eat = must_eat[i];
}

void	controller_init(int argc, char **argv,
	t_controller *controller, int n_philo)
{
	int		i;

	controller->n_philo = n_philo;
	controller->notepme = NULL;
	controller->philo_status = (int *) malloc(n_philo * sizeof(int));
	controller->turn = (int *) malloc(n_philo * sizeof(int));
	controller->n_groups = 2;
	controller->thread = NULL;
	if (controller->n_philo % 2 == 1)
		controller->n_groups = 3;
	if (argc >= 6)
	{
		controller->notepme = (int *) malloc(n_philo * sizeof(int));
		i = -1;
		while (++i < n_philo)
			controller->notepme[i] = atoi(argv[i + 5]);
	}
}

int	init(int argc, char **argv, t_data *dt)
{
	int			i;
	int			n_philo;

	n_philo = atoi(argv[1]);
	//mutexes & threads & philos MALLOCS
	dt->fork = (pthread_mutex_t *) malloc(n_philo * sizeof(pthread_mutex_t));
	dt->thread = (pthread_t *) malloc((n_philo + 1) * sizeof(pthread_t));
	dt->philo = (t_philo *) malloc(n_philo * sizeof(t_philo));
	dt->controller = (t_controller *) malloc(sizeof(t_controller));
	//controller
	controller_init(argc, argv, dt->controller, n_philo);
	dt->controller->thread = dt->thread;
	i = -1;
	printf("fork %p\nthread %p\nphilo %p\ncontroller %p\n", dt->fork, dt->thread, dt->philo, dt->controller);
	//philos
	while (++i < n_philo)
	{
		dt->controller->turn[i] = RED;
		philo_init(&dt->philo[i],
			(t_philo){{
			&dt->fork[((i + n_philo) % n_philo)],
			&dt->fork[((i + n_philo + 1) % n_philo)]},
			0, 0, 0, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
			i, &dt->controller->turn[i],
			&dt->controller->philo_status[i], 0, -1}, dt->controller->notepme, i); 
	}
	return (0);
}
