/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:53:04 by math              #+#    #+#             */
/*   Updated: 2024/04/11 19:53:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static int	clean_pid(pid_t *pid_list, int size, pid_t pid)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pid_list[i] == pid)
		{
			pid_list[i] = 0;
			return (0);
		}
	}
	return (1);
}

static void	kill_pid_list(pid_t *pid_list, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pid_list[i] > 0)
		{
			kill(pid_list[i], SIGKILL);
			pid_list[i] = 0;
		}
	}
}

void	wait_philos(pid_t *pid, int n_philo)
{
	int		i;
	int		status;
	pid_t	philo;

	i = -1;
	while (++i < n_philo)
	{
		philo = waitpid(-1, &status, 0);
		clean_pid(pid, n_philo, philo);
		if (WEXITSTATUS(status) == 1)
			return (kill_pid_list(pid, n_philo));
	}
	

}