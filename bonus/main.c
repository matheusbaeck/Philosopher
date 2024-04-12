/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:20:20 by math              #+#    #+#             */
/*   Updated: 2024/04/12 11:19:50 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	philo_sync(t_philo *ph)
{
	while (get_time() != ph->time_zero)
		;
	if (ph->phid % 2 == 0)
		usleep(100);
}

void philo_task(t_philo ph)
{
	ph.name = ph.phid + 1;
	ph.last_meal = ph.time_zero;
	ph.last_act = SLEEP;
	philo_sync(&ph);
	philo_loop(&ph);
}

void	clean(pid_t *pid, sem_t *semaphore)
{
	free(pid);
	pid = NULL;
	sem_destroy(semaphore);
}

int	main(int argc, char **argv)
{
	pid_t	*pid;
	sem_t 	*semaphore;
	int		n_philo;

	if (check_entry(argc, argv))
		return (1);
	n_philo = ft_atoi(argv[1]);
	if (init(&pid, n_philo, &semaphore))
		return (1);
	init_philo(argc, argv, pid, n_philo, semaphore);
	wait_philos(pid, n_philo);
	clean(pid, semaphore);
	return (0);
}
