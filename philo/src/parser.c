/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:55:04 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/01 20:12:21 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigits(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

t_ph	*ft_ph(void)
{
	static t_ph	x = {
		.n_philo = 0,
		.die = 0,
		.eat = 0,
		.sleep = 0,
		.times_eat = -1,
		.stomach_full = NULL,
		.ids = NULL,
		.forks = NULL,
		.philo = NULL,
		.lamuerte = 0,
		.data_meal = PTHREAD_MUTEX_INITIALIZER,
		.data_stomach = PTHREAD_MUTEX_INITIALIZER
	};

	return (&x);
}

static void	init_stomach(t_ph *ph)
{
	int	i;

	i = 0;
	ph->stomach_full = malloc(sizeof(int) * ph->n_philo);
	if (!ph->stomach_full)
		exit_error("Failed to allocate memory for philosophers.", ph);
	while (i < ph->n_philo)
		ph->stomach_full[i++] = 0;
}

t_ph	*ft_arg_parser(char **vargs)
{
	int		i;
	t_ph	*ph;

	i = 1;
	while (vargs[i])
	{
		if (!ft_strlen(vargs[i]) || !ft_isdigits(vargs[i])
			|| !ft_isint(vargs[i]) || !ft_atoi(vargs[i]))
			exit_error("Invalid argument: The argument must be a positive\
 non-zero integer.", NULL);
		i++;
	}
	ph = ft_ph();
	ph->n_philo = ft_atoi(vargs[1]);
	ph->die = ft_atoi(vargs[2]);
	ph->eat = ft_atoi(vargs[3]);
	ph->sleep = ft_atoi(vargs[4]);
	if (vargs[5])
	{
		ph->times_eat = ft_atoi(vargs[5]);
		init_stomach(ph);
	}
	return (ph);
}
