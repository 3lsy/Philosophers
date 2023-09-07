/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:24:11 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/07 20:00:27 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	acting(t_ph *ph, char *act_str, int id, t_ull *time_last_meal)
{
	t_ull	time;

	pthread_mutex_lock(&ph->data_print);
	if (check_termination(ph))
	{
		pthread_mutex_unlock(&ph->data_print);
		return (0);
	}
	time = get_timestamp_in_ms();
	if (time_last_meal)
		*time_last_meal = set_last_meal(ph, id, time);
	printf("%llu %d %s\n", time - ph->start_time, id + 1, act_str);
	pthread_mutex_unlock(&ph->data_print);
	return (1);
}

int	takes_forks(t_ph *ph, t_id *id, int lfork, int rfork)
{
	pthread_mutex_lock(&ph->forks[lfork]);
	if (!acting(ph, FORKING, id->id, NULL))
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
	if (!acting(ph, FORKING, id->id, NULL))
	{
		pthread_mutex_unlock(&ph->forks[lfork]);
		pthread_mutex_unlock(&ph->forks[rfork]);
		return (0);
	}
	return (1);
}

int	ph_eats(t_ph *ph, t_id *id, int lfork, int rfork)
{
	if (!acting(ph, EATING, id->id, &(id->time_last_meal)))
	{
		pthread_mutex_unlock(&ph->forks[lfork]);
		pthread_mutex_unlock(&ph->forks[rfork]);
		return (0);
	}
	set_eating(ph, id, 1);
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
	if (!acting(ph, SLEEPING, id->id, NULL))
		return (0);
	usleep(ph->sleep * 1000);
	set_eating(ph, id, 0);
	return (1);
}
