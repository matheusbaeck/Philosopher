/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/03/01 21:36:59 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	philo_init(t_philo *self, long int time, t_philo_init philo)
{
	self->time_zero = philo.time;
	self->time_to_die = philo.time_to_die;
	self->time_to_eat = philo.time_to_eat;
	self->time_to_sleep = philo.time_to_sleep;
	self->notepme = philo.notepme;
	self->fork[0] = NULL;
	self->fork[1] = NULL;
	self->mutex = philo.mutex;
	self->last_act = UNITIALIZED;
	self->phid = philo.phid;
	self->name = philo.phid + 1;
	self->time = time;
	self->last_meal = self->time;
	self->exs = philo.exs;
	self->exs->phid = self->phid;
	self->exs->name = self->name;
	self->exs->time_of_death = 0;
}

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
	if (dt->exs)
	{
		free(dt->exs);
		dt->exs = NULL;
	}
}

static void	init_data(t_data *dt, int n_philo, int time_to_die)
{
	dt->n_philo = n_philo;
	dt->time_to_die = time_to_die;
	dt->fork = (pthread_mutex_t *)malloc(dt->n_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&dt->mutex, NULL);
	dt->routine = (pthread_t *)malloc(dt->n_philo * sizeof(pthread_t));
	dt->philo = (t_philo *)malloc(dt->n_philo * sizeof(t_philo));
	dt->exs = (t_philo_exit *)malloc(dt->n_philo * sizeof(t_philo_exit));
	if (!(dt->fork && dt->routine && dt->philo && dt->exs))
	{
		printf("Philosopher: memory allocation error!\n");
		free_data(dt);
		exit(1);
	}
	dt->time_zero = get_time();
}

static int	init(int argc, char **argv, t_data *dt)
{
	int	i;
	int	black_hole;

	init_data(dt, atoi(argv[1]), atoi(argv[2]));
	i = -1;
	while (++i < dt->n_philo)
	{
		black_hole = -1;
		if (argc >= 6)
			black_hole = atoi(argv[5 + i]);
		philo_init(&dt->philo[i], dt->time_zero, (t_philo_init){i,
			dt->time_zero, dt->time_to_die, atoi(argv[3]), atoi(argv[4]),
			black_hole, &dt->mutex, &dt->exs[i]});
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
			dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo) % dt->n_philo)];
			dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
		}
		else
		{
			dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo) % dt->n_philo)];
			dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
		}
	}
	return (0);
}

static void	is_there_any_dead(t_data *dt)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < dt->n_philo)
		{
			pthread_mutex_lock(dt->philo[i].fork[0]);
			if (get_time() - dt->philo[i].last_meal >= dt->time_to_die)
			{
				printf("%ld\t\t%d is DEEEEEEEEEEEEEAD\n", get_time() - dt->time_zero, i + 1);
				exit (1);
			}
			pthread_mutex_unlock(dt->philo[i].fork[0]);
		}
		usleep(10 * dt->n_philo);
	}
	return ;
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
	dprintf(fd, "mutex\t\t%p\n", &dt.mutex);
	dprintf(fd, "exs\t\t%p\n", dt.exs);
	i = -1;
	while (++i < dt.n_philo)
	{
		dprintf(fd, "\n### %d ###\n", i);
		dprintf(fd, "born time\t%ld\n", dt.philo[i].time_zero);
		dprintf(fd, "time to die\t%ld\n", dt.philo[i].time_to_die);
		dprintf(fd, "time to sleep\t%ld\n", dt.philo[i].time_to_sleep);
		dprintf(fd, "time to eat\t%ld\n", dt.philo[i].time_to_eat);
		dprintf(fd, "notepme\t\t%d\n", dt.philo[i].notepme);
		dprintf(fd, "mutex\t\t%p\n", dt.philo[i].mutex);
		dprintf(fd, "exit sts\t%p\n", dt.philo[i].exs);
		dprintf(fd, "fork[0]\t\t%p\n", dt.philo[i].fork[0]);
		dprintf(fd, "fork[1]\t\t%p\n", dt.philo[i].fork[1]);
			// Corrected typo from forl[1] to fork[1]
		dprintf(fd, "last act\t%d\n", dt.philo[i].last_act);
		dprintf(fd, "phid\t\t%d\n", dt.philo[i].phid);
		dprintf(fd, "name\t\t%d\n", dt.philo[i].name);
		dprintf(fd, "time\t\t%ld\n", dt.philo[i].time);
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
	if (init(argc, argv, &dt) != 0)
		return (perror("init"), 1);
	set_forks(&dt);
	// print_data(dt);
	i = -1;
	while (++i < dt.n_philo)
	{
		if (pthread_create(&dt.routine[i], NULL, philo_loop, &dt.philo[i]) != 0)
			perror("pthread_create");
	}
	is_there_any_dead(&dt);
	i = -1;
	while (++i < dt.n_philo)
	{
		if (pthread_join(dt.routine[i], (void *)&dt.exs[i]) != 0)
		{
			perror("pthread_join");
		}
		else if ((void *)&dt.exs[i] != PTHREAD_CANCELED)
		{
			printf("%ld %d is dead %ld\n", get_time() - dt.time_zero,
				dt.exs[i].phid, dt.exs[i].time_of_death);
		}
		else
		{
			printf("WARNING !!!! Thread canceled\n");
		}
	}
	free_data(&dt);
	return (0);
}
