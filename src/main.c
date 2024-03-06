/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/03/06 22:20:48 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	free_data(t_data *dt)
{
	int	i;

	if (dt->fork)
	{
		i = -1;
		while (++i < dt->n_philo)
			pthread_mutex_destroy(&dt->fork[i]);
		free(dt->fork);
		dt->fork = NULL;
	}
	if (dt->routine)
	{
		free(dt->routine);
		dt->routine = NULL;
	}
	if (dt->philo)
	{
		free(dt->philo);
		dt->philo = NULL;
	}
}

static void	is_there_any_dead(t_data *dt)
{
	int	i;
	long int	last;

	while (1)
	{
		i = -1;
		while (++i < dt->n_philo)
		{
			last = get_last_meal(&dt->philo[i]);
			if (get_time() - last >= dt->time_to_die)
			{
				printf("%ld\t%d is DEAD\n", get_time() - dt->time_zero, i + 1);
				set_status(&dt->philo[i], -1);
				return ;
			}
			if (get_status(&dt->philo[i]) <= 0)
				return ;
		}
		usleep(25 * dt->n_philo);
	}
}

void	print_data(t_data dt)
{
	int	i;
	int	fd;

	#include <fcntl.h>
	// fd = open("data", O_CREAT);
	fd = 1;
	dprintf(fd, "\n### data ###\n");
	i = -1;
	dprintf(fd, "time_zero:\t%ld\n", dt.time_zero);
	dprintf(fd, "time_to_die:\t%d\n", dt.time_to_die);
	dprintf(fd, "philo:\t%d\n", dt.n_philo);
	while (++i < dt.n_philo)
	{
		dprintf(fd, "\t\t%p\n", &dt.philo[i]);
	}
	i = -1;
	dprintf(fd, "routine:\n");
	while (++i < dt.n_philo)
	{
		dprintf(fd, "\t\t%p\n", &dt.routine[i]);
	}
	i = -1;
	dprintf(fd, "fork:\n");
	while (++i < dt.n_philo)
	{
		dprintf(fd, "\t\t%p\n", &dt.fork[i]);
	}
	dprintf(fd, "mutex\t\t%p\n", &dt.mutex_lstmeal);
	dprintf(fd, "mutex\t\t%p\n", &dt.mutex_status);
	i = -1;
	while (++i < dt.n_philo)
	{
		dprintf(fd, "\n### %d ###\n", i);
		dprintf(fd, "born time\t%ld\n", dt.philo[i].time_zero);
		dprintf(fd, "time to die\t%ld\n", dt.philo[i].time_to_die);
		dprintf(fd, "time to sleep\t%ld\n", dt.philo[i].time_to_sleep);
		dprintf(fd, "time to eat\t%ld\n", dt.philo[i].time_to_eat);
		dprintf(fd, "notepme\t\t%d\n", dt.philo[i].notepme);
		dprintf(fd, "mutex\t\t%p\n", dt.philo[i].mutex_lstmeal);
		dprintf(fd, "mutex\t\t%p\n", dt.philo[i].mutex_status);
		dprintf(fd, "fork[0]\t\t%p\n", dt.philo[i].fork[0]);
		dprintf(fd, "fork[1]\t\t%p\n", dt.philo[i].fork[1]);
			// Corrected typo from forl[1] to fork[1]
		dprintf(fd, "last act\t%d\n", dt.philo[i].last_act);
		dprintf(fd, "phid\t\t%d\n", dt.philo[i].phid);
		dprintf(fd, "name\t\t%d\n", dt.philo[i].name);
		dprintf(fd, "last meal\t%ld\n", dt.philo[i].last_meal);
	}
	close(fd);
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
	is_there_any_dead(&dt);
	i = -1;
	while (++i < dt.n_philo)
		pthread_join(dt.routine[i], NULL);
	free_data(&dt);
	return (0);
}
