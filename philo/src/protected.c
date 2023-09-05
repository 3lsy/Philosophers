/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:26:14 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/05 18:44:43 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	terminate_program(t_ph *ph)
{
	pthread_mutex_lock(&ph->data_termination);
	ph->terminate_program = 1;
	pthread_mutex_unlock(&ph->data_termination);
}

int	check_termination(t_ph *ph)
{
	int	terminate_program;

	pthread_mutex_lock(&ph->data_termination);
	terminate_program = ph->terminate_program;
	pthread_mutex_unlock(&ph->data_termination);
	return (terminate_program);
}

void	stomach_full(t_ph *ph, int id)
{
	pthread_mutex_lock(&ph->data_stomach);
	ph->stomach_full[id] = 1;
	pthread_mutex_unlock(&ph->data_stomach);
}

int	check_if_full(t_ph *ph, int id)
{
	int	stomach_full;

	pthread_mutex_lock(&ph->data_stomach);
	stomach_full = ph->stomach_full[id];
	pthread_mutex_unlock(&ph->data_stomach);
	return (stomach_full);
}

t_ull	set_last_meal(t_ph *ph, int id, t_ull time)
{
	pthread_mutex_lock(&ph->data_meal);
	ph->last_meal[id] = time;
	pthread_mutex_unlock(&ph->data_meal);
	return (time);
}
