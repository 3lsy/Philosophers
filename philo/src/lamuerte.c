/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lamuerte.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:34:22 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/04 13:53:02 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_someone_died(t_ph *ph, int i)
{
	unsigned long long	time_last_meal;

	pthread_mutex_lock(&ph->data_meal);
	time_last_meal = ph->ids[i].time_last_meal;
	if (get_timestamp_in_ms() - time_last_meal
		> (unsigned long long)ph->die)
	{
		printf("%llu %d died\n", get_timestamp_in_ms(), i + 1);
		pthread_mutex_unlock(&ph->data_meal);
		ft_destructor(ph);
		exit(0);
	}
	pthread_mutex_unlock(&ph->data_meal);
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
			check_someone_died(ph, i);
			if (ph->times_eat != -1)
			{
				pthread_mutex_lock(&ph->data_stomach);
				everyone_full *= ph->stomach_full[i];
				pthread_mutex_unlock(&ph->data_stomach);
			}
			i++;
		}
		if (ph->times_eat != -1 && everyone_full)
		{
			ft_destructor(ph);
			exit(0);
		}
	}
	return (NULL);
}
