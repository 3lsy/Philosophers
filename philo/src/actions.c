/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:24:11 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/05 20:04:59 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	acting(t_ph *ph, char *act_str, int id, t_ull time)
{
	if (check_termination(ph))
		return (0);
	pthread_mutex_lock(&ph->data_print);
	printf("%llu %d %s\n", time, id + 1, act_str);
	pthread_mutex_unlock(&ph->data_print);
	return (1);
}

int	takes_forks(t_ph *ph, t_id *id, int lfork, int rfork)
{
	if (!acting(ph, THINKING, id->id, get_timestamp_in_ms()))
		return (0);
	pthread_mutex_lock(&ph->forks[lfork]);
	if (!acting(ph, FORKING, id->id, get_timestamp_in_ms()))
	{
		pthread_mutex_unlock(&ph->forks[lfork]);
		return (0);
	}
	if (lfork == rfork)
	{
		pthread_mutex_unlock(&ph->forks[lfork]);
		while (check_termination(ph))
			usleep(1000);
		return (0);
	}
	pthread_mutex_lock(&ph->forks[rfork]);
	if (!acting(ph, FORKING, id->id, get_timestamp_in_ms()))
	{
		pthread_mutex_unlock(&ph->forks[lfork]);
		pthread_mutex_unlock(&ph->forks[rfork]);
		return (0);
	}
	return (1);
}

int	ph_eats(t_ph *ph, t_id *id, int lfork, int rfork)
{
	id->time_last_meal = set_last_meal(ph, id->id, get_timestamp_in_ms());
	if (!acting(ph, EATING, id->id, id->time_last_meal))
	{
		pthread_mutex_unlock(&ph->forks[lfork]);
		pthread_mutex_unlock(&ph->forks[rfork]);
		return (0);
	}
	id->meal_counter++;
	usleep(ph->eat * 1000);
	pthread_mutex_unlock(&ph->forks[lfork]);
	pthread_mutex_unlock(&ph->forks[rfork]);
	if (ph->times_eat != -1 && id->meal_counter == ph->times_eat)
		stomach_full(ph, id->id);
	return (1);
}

int	ph_sleeps(t_ph *ph, t_id *id)
{
	if (!acting(ph, SLEEPING, id->id, get_timestamp_in_ms()))
		return (0);
	usleep(ph->sleep * 1000);
	return (1);
}
