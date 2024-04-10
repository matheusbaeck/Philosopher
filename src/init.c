/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/04/10 18:34:37 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	set_forks(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < dt->n_philo)
	{
		if (i % 2 == 0 || dt->n_philo % 2 == 1)
		{
			dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo) % dt->n_philo)];
			dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo + 1)
					% dt->n_philo)];
		}
		else
		{
			dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo) % dt->n_philo)];
			dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo + 1)
					% dt->n_philo)];
		}
	}
}

static int	init_mutexes(t_data *dt)
{
	int	i;

	if (pthread_mutex_init(&dt->mutex_status, NULL))
		return (printf("Philosopher: failed to init mutex\n"), 1);
	i = -1;
	while (++i < dt->n_philo)
	{
		if (pthread_mutex_init(&dt->fork[i], NULL))
		{
			pthread_mutex_destroy(&dt->mutex_status);
			destroy_mutex_array(&dt->fork[i], i - 1);
			destroy_mutex_array(&dt->mutex_philo_att[i], i - 2);
			return (printf("Philosopher: failed to init mutex\n"), 1);
		}
		if (pthread_mutex_init(&dt->mutex_philo_att[i], NULL))
		{
			pthread_mutex_destroy(&dt->mutex_status);
			destroy_mutex_array(&dt->fork[i], i);
			destroy_mutex_array(&dt->mutex_philo_att[i], i - 1);
			return(printf("Philosopher: failed to init mutex\n"), 1);
		}
	}
	return (0);
}

static void	philo_init(t_philo *self, t_philo_init philo)
{
	self->time_zero = philo.time_zero;
	self->time_to_die = philo.time_to_die;
	self->time_to_eat = philo.time_to_eat;
	self->time_to_sleep = philo.time_to_sleep;
	self->notepme = philo.notepme;
	self->mutex_philo_att = philo.mutex_philo_att;
	self->mutex_status = philo.mutex_status;
	self->fork[0] = NULL;
	self->fork[1] = NULL;
	self->status = philo.status;
	self->phid = philo.phid;
	self->name = philo.phid + 1;
	self->last_meal = philo.time_zero;
	self->last_act = SLEEP;
}

static int	init_data(t_data *dt, int n_philo, int time_to_die)
{
	dt->n_philo = n_philo;
	dt->time_to_die = time_to_die;
	dt->status = dt->n_philo;
	dt->fork = (pthread_mutex_t *)malloc(dt->n_philo * sizeof(pthread_mutex_t));
	dt->mutex_philo_att = (pthread_mutex_t *)malloc(dt->n_philo
			* sizeof(pthread_mutex_t));
	dt->routine = (pthread_t *)malloc(dt->n_philo * sizeof(pthread_t));
	dt->philo = (t_philo *)malloc(dt->n_philo * sizeof(t_philo));
	if (!(dt->fork && dt->routine && dt->philo && dt->mutex_philo_att))
	{
		free_data(dt);
		printf("Philosopher: memory allocation error!\n");
		return (1);
	}
	dt->time_zero = get_time() + 100 + (2 * dt->n_philo);
	return (0);
}

int	init(int argc, char **argv, t_data *dt)
{
	int	i;
	int	notepme;

	if (init_data(dt, ft_atoi(argv[1]), ft_atoi(argv[2])))
		return (1);
	notepme = -1;
	if (argc >= 6)
		notepme = ft_atoi(argv[5]);
	i = -1;
	while (++i < dt->n_philo)
	{
		philo_init(&dt->philo[i], (t_philo_init){i, dt->time_zero,
			dt->time_to_die, ft_atoi(argv[3]), ft_atoi(argv[4]),
			notepme, &dt->status, &dt->mutex_philo_att[i],
			&dt->mutex_status});
	}
	if (init_mutexes(dt))
		return (free_data(dt), 1);
	set_forks(dt);
	return (0);
}
