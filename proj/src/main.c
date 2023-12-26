/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2023/12/26 13:50:01 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void free_data(t_data *dt, int *status)
{
	int i;

	i = -1;
	while (++i < dt->controller->n_philo)
		pthread_mutex_destroy(&dt->fork[i]);
	free(dt->fork);
	free(dt->thread);
	free(dt->philo);
	free(dt->controller->philo_status);
	free(dt->controller->turn);
	i = -1;
	if (dt->controller->notepme)
		free(dt->controller->notepme);
	free(dt->controller);
	free(status);
}

void	kill_them_all(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < dt->controller->n_philo)
	{
		if (dt->philo->status[i] != DEAD)
		{
			printf("Killing %i %ld :%i\n", i, dt->controller->thread[i], dt->controller->philo_status[i]);
			kill(dt->controller->thread[i], 1);
		}
		else
			printf("Killing %i ALREADY DEAD", i);
	}
}

int	main(int argc, char **argv)
{
	t_data			dt;
	int				i;
	void			*status;

	if (argc < 5)
		return (perror("few args"), 1);
	if (init(argc, argv, &dt))
		return (perror("init fail"), 1);
	i = -1;
	while (++i < dt.controller->n_philo)
	{
		pthread_create(&dt.thread[i], NULL, philo_loop, &dt.philo[i]);
		pthread_detach(dt.thread[i]);
	}
	pthread_create(&dt.thread[i], NULL, controller_loop, dt.controller);
	pthread_join(dt.thread[i], &status);
	printf("END:%i\n", *((int *) status));
	kill_them_all(&dt);
	free_data(&dt, (int *) status);
	return (0);
}
