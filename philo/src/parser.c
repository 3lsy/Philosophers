/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:55:04 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/05 18:30:21 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigits(char *arg)
{
	int	i;

	if (ft_strlen(arg) == 0)
		return (0);
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
		.terminate_program = 0,
		.last_meal = NULL,
		.stomach_full = NULL,
		.ids = NULL,
		.forks = NULL,
		.philo = NULL,
		.lamuerte = 0,
		.data_meal = PTHREAD_MUTEX_INITIALIZER,
		.data_stomach = PTHREAD_MUTEX_INITIALIZER,
		.data_termination = PTHREAD_MUTEX_INITIALIZER,
		.data_print = PTHREAD_MUTEX_INITIALIZER
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

static void	valid_args(char **vargs)
{
	if (!ft_isdigits(vargs[1]) || !ft_isint(vargs[1]) || !ft_atoi(vargs[1]))
		exit_error("Invalid argument: \
The argument must be a non-zero integer.", NULL);
	if (
		!ft_isdigits(vargs[2]) || !ft_isull(vargs[2]) || !ft_atoull(vargs[2])
		|| !ft_isdigits(vargs[3]) || !ft_isull(vargs[3]) || !ft_atoull(vargs[3])
		|| !ft_isdigits(vargs[4]) || !ft_isull(vargs[4]) || !ft_atoull(vargs[4])
	)
		exit_error("Invalid argument: \
The argument must be a non-zero unsigned long long millisec.", NULL);
	if (
		vargs[5] 
		&& (!ft_isdigits(vargs[5]) || !ft_isint(vargs[5]) || !ft_atoi(vargs[5]))
	)
		exit_error("Invalid argument: \
The argument must be a non-zero integer.", NULL);
}

t_ph	*ft_arg_parser(char **vargs)
{
	t_ph	*ph;
	int		i;

	valid_args(vargs);
	ph = ft_ph();
	ph->n_philo = ft_atoi(vargs[1]);
	ph->die = ft_atoull(vargs[2]);
	ph->eat = ft_atoull(vargs[3]);
	ph->sleep = ft_atoull(vargs[4]);
	if (vargs[5])
	{
		ph->times_eat = ft_atoi(vargs[5]);
		init_stomach(ph);
	}
	ph->last_meal = malloc(sizeof(t_ull) * ph->n_philo);
	if (!ph->last_meal)
		exit_error("Failed to allocate memory for philosophers.", ph);
	i = 0;
	while (i < ph->n_philo)
		ph->last_meal[i++] = 0;
	return (ph);
}
