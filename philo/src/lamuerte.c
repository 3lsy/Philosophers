/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lamuerte.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:34:22 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/07 15:01:12 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_ull	get_last_meal(t_ph *ph, int id)
{
	t_ull	time_last_meal;

	pthread_mutex_lock(&ph->data_meal);
	time_last_meal = ph->last_meal[id];
	pthread_mutex_unlock(&ph->data_meal);
	return (time_last_meal);
}

static int	ph_died(t_ph *ph, int id)
{
	t_ull	time_last_meal;

	time_last_meal = get_last_meal(ph, id);
	if (get_timestamp_in_ms() - time_last_meal > (t_ull)ph->die)
	{
		acting(ph, DEAD, id, get_timestamp_in_ms());
		terminate_program(ph);
		return (1);
	}
	return (0);
}

static int	check_every_philosopher(t_ph *ph)
{
	int	id;
	int	everyone_full;

	id = 0;
	everyone_full = 1;
	while (id < ph->n_philo)
	{
		if (ph_died(ph, id))
			return (0);
		if (ph->times_eat != -1)
			everyone_full *= check_if_full(ph, id);
		id++;
	}
	if (ph->times_eat != -1 && everyone_full)
	{
		terminate_program(ph);
		return (0);
	}
	return (1);
}

void	*lamuerte(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	while (1)
	{
		usleep(2000);
		if (!check_every_philosopher(ph))
			return (NULL);
	}
	return (NULL);
}
