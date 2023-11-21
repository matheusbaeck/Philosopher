/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math42 <math42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:42:37 by math42            #+#    #+#             */
/*   Updated: 2023/11/21 17:56:51 by math42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		dt->philo[i].fork[0] = &dt->fork[((i + n_philo) % n_philo)];
		dt->philo[i].fork[1] = &dt->fork[((i + n_philo + 1) % n_philo)];
	}
	return (0);
}

// int set_forks(t_data *dt)
// {
//     int i;

//     i = -1;
//     while (++i < dt->n_philo)
//     {
//         if (pthread_mutex_init(&dt->fork[i], NULL))
//             printf("fork %d fail at %p\n", i, &dt->fork[i]);
//     }
//     i = -1;
//     while (++i < dt->n_philo)
//     {
//         if (i % 2 == 0)
//         {
//             dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo) % dt->n_philo)];
//             dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
//             dt->philo[i].fname[0] = (i + dt->n_philo) % dt->n_philo;
//             dt->philo[i].fname[1] = (i + dt->n_philo + 1) % dt->n_philo;
//         }
//         else
//         {
//             dt->philo[i].fork[1] = &dt->fork[((i + dt->n_philo) % dt->n_philo)];
//             dt->philo[i].fork[0] = &dt->fork[((i + dt->n_philo + 1) % dt->n_philo)];
//             dt->philo[i].fname[1] = (i + dt->n_philo) % dt->n_philo;
//             dt->philo[i].fname[0] = (i + dt->n_philo + 1) % dt->n_philo;
//         }
//         printf("%i has forks %i %i\n", i + 1, dt->philo[i].fname[0] + 1, dt->philo[i].fname[1] + 1);
//     }
//     return (0);
// }

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
		if (*(ph->status) == NOT_INIT || *(ph->status) == SLP)
			think(ph);
		else if (*(ph->status) == THK)
		{
			if (eat(ph) == -1)
				return (printf("%d died trying to eat\n", ph->name), NULL);
		}
		else if (*(ph->status) == EAT)
			psleep(ph);
		get_time(ph);
	}
	printf("EXIT %d\n", ph->name);
	return (NULL);
}
