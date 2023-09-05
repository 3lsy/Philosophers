/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lamuerte.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:34:22 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/05 18:20:20 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_died(t_ph *ph, int i)
{
	t_ull	time_last_meal;

	pthread_mutex_lock(&ph->data_meal);
	time_last_meal = ph->last_meal[i];
	pthread_mutex_unlock(&ph->data_meal);
	if (get_timestamp_in_ms() - time_last_meal > (t_ull)ph->die)
	{
		acting(ph, DEAD, i, get_timestamp_in_ms());
		terminate_program(ph);
		return (1);
	}
	return (0);
}

void	*lamuerte(void *arg)
{
	t_ph				*ph;
	int					i;
	int					everyone_full;

	ph = (t_ph *)arg;
	while (1)
	{
		usleep(1000);
		i = 0;
		everyone_full = 1;
		while (i < ph->n_philo)
		{
			if (ph_died(ph, i))
				return (NULL);
			if (ph->times_eat != -1)
				everyone_full *= check_if_full(ph, i);
			i++;
		}
		if (ph->times_eat != -1 && everyone_full)
		{
			terminate_program(ph);
			return (NULL);
		}
	}
	return (NULL);
}
