/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:50:50 by math              #+#    #+#             */
/*   Updated: 2024/04/12 11:22:13 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	init_philo(int argc, char **argv, pid_t *pid, int n_philo, sem_t *semaphore)
{
	int			i;
	long int	time_zero;
	t_philo 	ph;

	i = -1;
	time_zero = get_time() + 200;
	ph.semaphore = semaphore;
	ph.time_zero = time_zero;
	ph.time_to_die = ft_atoi(argv[2]);
	ph.time_to_eat = ft_atoi(argv[3]);
	ph.time_to_sleep = ft_atoi(argv[4]);
	ph.notepme = -1;
	if (argc >= 6)
		ph.notepme = ft_atoi(argv[5]);
	while (++i < n_philo)
	{
		ph.phid = i;
		pid[i] = fork();
		if (pid[i] == 0)
			philo_task(ph);
	}
}

int	init(pid_t **pid, int n_philo, sem_t **semaphore)
{
	*pid = (pid_t *)malloc(n_philo * sizeof(pid_t));
	if (!pid)
		return (1);
	sem_unlink("forks");
	*semaphore = sem_open("forks", O_CREAT, 0644, n_philo);
	if (!*semaphore)
		return (1);
	return (0);
}