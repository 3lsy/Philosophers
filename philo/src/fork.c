/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:13:56 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/05 18:44:51 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_ph	*destroy_forks(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->n_philo)
		pthread_mutex_destroy(&ph->forks[i++]);
	free(ph->forks);
	ph->forks = NULL;
	return (ph);
}

t_ph	*create_forks(t_ph *ph)
{
	int	i;

	i = 0;
	ph->forks = malloc(sizeof(pthread_mutex_t) * ph->n_philo);
	if (!ph->forks)
		exit_error("Failed to allocate memory for forks.", ph);
	while (i < ph->n_philo)
		if (pthread_mutex_init(&ph->forks[i++], NULL) != 0)
			exit_error("Failed to initialize mutex.", ph);
	return (ph);
}
