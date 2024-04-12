/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:57:53 by math              #+#    #+#             */
/*   Updated: 2024/04/12 11:27:28 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static int	is_alive(t_philo *ph)
{
	if (get_time() - ph->last_meal > ph->time_to_die)
	{
		printf("%ld\t%d is DEAD\n", get_time() - ph->time_zero
			, ph->name);
		exit (1);
	}
	return (1);
}

static void	think(t_philo *ph)
{
	ph->last_act = THINK;
	printf("%ld\t\t%d is thinking\n", get_print_time(ph), ph->name);
}

static void	eat(t_philo *ph)
{
	ph->last_act = EAT;
	sem_wait(ph->semaphore);
	if (is_alive(ph))
		printf("%ld\t\t%d has taken a fork\n", get_print_time(ph), ph->name);
	sem_wait(ph->semaphore);
	if (is_alive(ph))
	{
		printf("%ld\t\t%d has taken a fork\n", get_print_time(ph), ph->name);
		printf("%ld\t\t%d is eating\n", get_print_time(ph), ph->name);
	}
	ph->last_meal = get_time();
	sleep_ms(ph->time_to_eat);
	sem_post(ph->semaphore);
	sem_post(ph->semaphore);
	ph->notepme --;
	if (ph->notepme == 0)
		exit (0);
	sleep_ms(ph->time_to_sleep);
}

static void	philo_sleep(t_philo *ph)
{
	ph->last_act = SLEEP;
	printf("%ld\t\t%d is sleeping\n", get_print_time(ph), ph->name);
	sleep_ms(ph->time_to_sleep);
}

void	philo_loop(t_philo *ph)
{
	while (is_alive(ph))
	{
		if (ph->last_act == SLEEP)
			think(ph);
		else if (ph->last_act == THINK)
			eat(ph);
		else if (ph->last_act == EAT)
			philo_sleep(ph);
	}
}