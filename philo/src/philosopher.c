/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:18:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/05 19:20:14 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	*philosopher(void *arg)
{
	t_id					*id;
	t_ph					*ph;

	id = (t_id *)arg;
	ph = id->ph;
	id->time_last_meal = set_last_meal(ph, id->id, get_timestamp_in_ms());
	id->meal_counter = 0;
	while (1)
	{
		if (!takes_forks(ph, id, id->id, (id->id + 1) % ph->n_philo))
			return (NULL);
		if (!ph_eats(ph, id, id->id, (id->id + 1) % ph->n_philo))
			return (NULL);
		if (!ph_sleeps(ph, id))
			return (NULL);
	}
	return (NULL);
}

t_ph	*create_philosophers(t_ph *ph)
{
	int		i;

	ph->ids = malloc(sizeof(t_id) * ph->n_philo);
	if (!ph->ids)
		exit_error("Failed to allocate memory for philosophers.", ph);
	ph->philo = malloc(sizeof(pthread_t) * ph->n_philo);
	if (!ph->philo)
		exit_error("Failed to allocate memory for philosophers.", ph);
	i = 0;
	while (i < ph->n_philo)
	{
		ph->ids[i].ph = ph;
		ph->ids[i].id = i;
		pthread_create(&ph->philo[i], NULL, philosopher, (void *)&ph->ids[i]);
		i++;
	}
	return (ph);
}
