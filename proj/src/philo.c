/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2023/11/16 15:03:37 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_init(t_philo *philo, t_philo param)
{
	*philo = param;

	pthread_mutex_init(philo->fork[0], NULL);
	*(philo->status) = THK;
	get_time(philo);
	philo->born_time = philo->time;
	philo->last_meal = philo->time;	
}

int	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

int	set_forks(t_data *dt, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_mutex_init(&dt->fork[i], NULL))
			printf("fork %d fail at %p\n", i, &dt->fork[i]);
	}
	i = -1;
	while (++ i < n_philo)
	{
		dt->philo[i].fork[0] = &dt->fork[((i + n_philo - 1) % n_philo)];
		dt->philo[i].fork[1] = &dt->fork[((i + n_philo + 1) % n_philo)];
	}
	return (0);
}

// void	init_test(t_philo *ph)
// {
// 	//INIT values
// 	printf("ph->NAME %i\n", ph->name);
// 	printf("ph->born_time %li\n", ph->born_time);
// 	printf("ph->time %li\n", ph->time);
// 	printf("ph->last_meal %li\n", ph->last_meal);
// 	printf("ph->time_to_die %li\n", ph->time_to_die);
// 	printf("ph->time_to_eat %li\n", ph->time_to_eat);
// 	printf("ph->time_to_sleep %li\n", ph->time_to_sleep);
// 	printf("ph->action %p\n", ph->last_act);
// 	printf("ph->turn %p %i\n", ph->turn, *ph->turn);
// 	printf("ph->status %p %i\n", ph->status, *ph->status);
// }

// void	mutex_test(t_philo *ph)
// {
// 	//MUTEX TEST
// 	if (ph->name == 0)
// 	{
// 		printf("philo %i lock own fork (%i)\n", ph->name, try_lock(ph->fork[0]));
// 		// printf("philo %i lock own fork (%i)\n", ph->name, try_lock(ph->fork[1]));
// 		// printf("philo %i unlocked own fork (%i)\n", ph->name, pthread_mutex_unlock(ph->fork[0]));
// 		// printf("philo %i unlocked own fork (%i)\n", ph->name, pthread_mutex_unlock(ph->fork[1]));
// 		pwait(2);
// 	}
// 	else if (ph->name == 1)
// 		pwait(4);
// 	else
// 		pwait(6);
// 	//exit(0);
// }	

void	*philo_loop(void *philo)
{
	t_philo	*ph;

	ph = ((t_philo *)philo);

	//init_test(ph);
	// mutex_test(ph);
	// while (*ph->turn == -1)
	// {
	// 	usleep(1000);
	// }
	get_time(ph);
	while ((ph->time - ph->last_meal) < ph->time_to_die)
	{
		if (ph->last_act == NULL || ph->last_act == psleep)
			think(ph);
		else if (ph->last_act == think)
		{
			if (eat(ph) == -1)
				return (printf("%d died trying to eat\n", ph->name), NULL);
		}
		else if (ph->last_act == eat)
			psleep(ph);
		get_time(ph);
	}
	printf("EXIT %d\n", ph->name);
	return (NULL);
}
