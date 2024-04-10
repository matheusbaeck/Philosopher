/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2024/04/10 18:07:55 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static void	is_there_any_dead(t_data *dt)
{
	int			i;
	long int	last;
	long int	time;
	int			notepme;
	int			count_notepme;

	time = get_time();
	while (1)
	{
		while (get_time() - time < 1)
			;
		i = -1;
		count_notepme = 0;
		while (++i < dt->n_philo)
		{
			last = get_last_meal(&dt->philo[i]);
			notepme = get_notepme(&dt->philo[i]);
			if (((get_time() - last) > dt->time_to_die))
			{
				set_status(&dt->philo[i], -1);
				printf("%ld\t%d is dead\n", get_time() - dt->time_zero, i + 1);
				return ;
			}
			if (notepme == 0)
				count_notepme ++;
		}
		if (count_notepme == dt->n_philo)
			return ;
		time = get_time();
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
	destroy_mutex(&dt);
	free_data(&dt);
	return (0);
}
