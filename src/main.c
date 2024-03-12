/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/03/12 17:20:55 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	free_aux(t_data *dt)
{
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
	if (dt->mutex_philo_att)
	{
		i = -1;
		while (++i < dt->n_philo)
			pthread_mutex_destroy(&dt->mutex_philo_att[i]);
		free(dt->mutex_philo_att);
		dt->mutex_philo_att = NULL;
	}
	free_aux(dt);
}

static void	is_there_any_dead(t_data *dt)
{
	int			i;
	long int	last;
	int			notepme;

	while (1)
	{
		i = -1;
		while (++i < dt->n_philo)
		{
			last = get_last_meal(&dt->philo[i]);
			notepme = get_notepme(&dt->philo[i]);
			if (get_time() - last >= dt->time_to_die && notepme != 0)
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
