/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/02/27 14:16:48 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	philo_init_cpy(t_philo *dest, t_philo_init philo)
{
	dest->phid = philo.phid;
	dest->born_time = philo.time;
	dest->time_to_die = philo.time_to_die;
	dest->time_to_eat = philo.time_to_eat;
	dest->time_to_sleep = philo.time_to_sleep;
	dest->notepme = philo.notepme;
}

static void	philo_init(t_philo *dest, t_philo_init philo)
{
	philo_init_cpy(dest, philo);
	get_time(dest);
	dest->name = philo.phid + 1;
	dest->last_meal = dest->time;
	dest->last_act = (void *) NULL;
}

static int	init(int argc, char **argv, t_data *dt)
{
	int				i;
	int				black_hole;
	long int		time;
	struct timeval	tv;

	dt->n_philo = atoi(argv[1]);
	i = -1;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (++i < dt->n_philo)
	{
		black_hole = -1;
		if (argc >= 6)
			black_hole = atoi(argv[5 + i]);
		philo_init(&dt->philo[i],
			(t_philo_init){i, time, atoi(argv[2]),
			atoi(argv[3]), atoi(argv[4]), black_hole});
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

	if (check_entry(argc, argv))
		return (1);
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
	printf("FINISH\n");
	return (0);
}
