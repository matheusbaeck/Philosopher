/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:00 by math42            #+#    #+#             */
/*   Updated: 2023/11/21 17:57:12 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data			dt;
	int				i;

	if (argc < 5)
		return (perror("few args"), 1);
	if (init(argc, argv, &dt))
		return (perror("init fail"), 1);
	i = -1;
	while (++i < dt.controller->n_philo)
	{
		pthread_create(&dt.thread[i], NULL, philo_loop, &dt.philo[i]);
	}
	pthread_create(&dt.thread[i], NULL, controller_loop, dt.controller);
	i = -1;
	while (++i < dt.controller->n_philo)
	{
		pthread_join(dt.thread[i], NULL);
	}
	return (0);
}
