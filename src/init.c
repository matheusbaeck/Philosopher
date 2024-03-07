/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/03/07 11:20:05 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	philo_init(t_philo *self, t_philo_init philo)
{
	self->time_zero = philo.time_zero;
	self->time_to_die = philo.time_to_die;
	self->time_to_eat = philo.time_to_eat;
	self->time_to_sleep = philo.time_to_sleep;
	self->notepme = philo.notepme;
	self->mutex_philo_att = philo.mutex_philo_att;
	pthread_mutex_init(self->mutex_philo_att, NULL);
	self->mutex_status = philo.mutex_status;
	self->fork[0] = NULL;
	self->fork[1] = NULL;
	self->status = philo.status;
	self->last_act = SLEEP;
	self->phid = philo.phid;
	self->name = philo.phid + 1;
	self->last_meal = philo.time_zero;
}

static void	set_forks(t_data *dt)
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
}

static int	init_data(t_data *dt, int n_philo, int time_to_die)
{
	dt->n_philo = n_philo;
	dt->time_to_die = time_to_die;
	dt->fork = (pthread_mutex_t *)malloc(dt->n_philo * sizeof(pthread_mutex_t));
	dt->mutex_philo_att = (pthread_mutex_t *)malloc(dt->n_philo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&dt->mutex_status, NULL);
	dt->routine = (pthread_t *)malloc(dt->n_philo * sizeof(pthread_t));
	dt->philo = (t_philo *)malloc(dt->n_philo * sizeof(t_philo));
	dt->status = dt->n_philo;
	if (!(dt->fork && dt->routine && dt->philo && dt->mutex_philo_att))
	{
		printf("Philosopher: memory allocation error!\n");
		return(1);
	}
	dt->time_zero = get_time();
	return (0);
}

int	init(int argc, char **argv, t_data *dt)
{
	int	i;
	int	j;
	int	black_hole;

	if (init_data(dt, atoi(argv[1]), atoi(argv[2])))
		return (free(dt), 1);
	i = -1;
	j = -1;
	while (++i < dt->n_philo)
	{
		black_hole = -1;
		if (argc >= 6)
		{
			black_hole = atoi(&argv[5][++j]);
			printf("%d eats %d times\n", i+1, black_hole);
			j += ft_strlen(&argv[5][j]);
		}
		philo_init(&dt->philo[i], (t_philo_init){i,
			dt->time_zero, dt->time_to_die, atoi(argv[3]), atoi(argv[4]),
			black_hole, &dt->status, &dt->mutex_philo_att[i], &dt->mutex_status});
	}
	set_forks(dt);
	return (0);
}