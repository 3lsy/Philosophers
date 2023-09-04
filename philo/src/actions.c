/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:24:11 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/01 20:14:06 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_forks(t_ph *ph, t_id *id, int lfork, int rfork)
{
	printf("%llu %d is thinking\n", get_timestamp_in_ms(), id->id + 1);
	pthread_mutex_lock(&ph->forks[lfork]);
	printf("%llu %d has taken a fork\n", get_timestamp_in_ms(), id->id + 1);
	pthread_mutex_lock(&ph->forks[rfork]);
	printf("%llu %d has taken a fork\n", get_timestamp_in_ms(), id->id + 1);
}

void	ph_eats(t_ph *ph, t_id *id, int lfork, int rfork)
{
	pthread_mutex_lock(&ph->data_meal);
	id->time_last_meal = get_timestamp_in_ms();
	pthread_mutex_unlock(&ph->data_meal);
	printf("%llu %d is eating\n", id->time_last_meal, id->id + 1);
	id->meal_counter++;
	usleep(ph->eat * 1000);
	pthread_mutex_unlock(&ph->forks[lfork]);
	pthread_mutex_unlock(&ph->forks[rfork]);
	pthread_mutex_lock(&ph->data_stomach);
	if (ph->times_eat != -1 && id->meal_counter == ph->times_eat)
		ph->stomach_full[id->id] = 1;
	pthread_mutex_unlock(&ph->data_stomach);
}

void	ph_sleeps(t_ph *ph, t_id *id)
{
	printf("%llu %d is sleeping\n", get_timestamp_in_ms(), id->id + 1);
	usleep(ph->sleep * 1000);
}