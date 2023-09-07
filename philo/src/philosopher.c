/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:18:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/07 19:12:09 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_eating(t_ph *ph, t_id *id, int eating)
{
	pthread_mutex_lock(&ph->data_eating);
	ph->eating[id->id] = eating;
	pthread_mutex_unlock(&ph->data_eating);
}

static int	every_odd_eats(t_ph *ph)
{
	int	id;
	int	is_eating;

	id = 1;
	while (id < ph->n_philo)
	{
		pthread_mutex_lock(&ph->data_eating);
		is_eating = ph->eating[id];
		pthread_mutex_unlock(&ph->data_eating);
		if (!is_eating)
			return (0);
		id += 2;
	}
	return (1);
}

static int	too_much_thinking(t_ph *ph, t_ull time_thinking)
{
	t_ull	time_limit;

	time_limit = ph->eat * 0.5;
	if (get_timestamp_in_ms() - time_thinking > time_limit)
		return (1);
	if (!every_odd_eats(ph))
		return (0);
	return (1);
}

static void	*philosopher(void *arg)
{
	t_id					*id;
	t_ph					*ph;
	t_ull					time_thinking;

	id = (t_id *)arg;
	ph = id->ph;
	id->time_last_meal = set_last_meal(ph, id->id, ph->start_time);
	id->meal_counter = 0;
	while (!check_termination(ph))
	{
		if (!acting(ph, THINKING, id->id, NULL))
			return (NULL);
		time_thinking = get_timestamp_in_ms();
		while (id->id % 2 == 0 && !too_much_thinking(ph, time_thinking))
			usleep(500);
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
	ph->start_time = get_timestamp_in_ms();
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
