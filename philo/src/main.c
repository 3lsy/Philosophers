/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:43:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/12 20:06:31 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		ft_analyzer(av);
		return (0);
	}
	ft_putendl_fd("There must be 4 to 5 arguments", 2);
	ft_putendl_fd("Usage: ./philo arg1 arg2 arg3 arg4 [arg5]", 2);
	ft_putendl_fd("In which:", 2);
	ft_putendl_fd(" arg1 : number_of_philosophers", 2);
	ft_putendl_fd(" arg2 : time_to_die", 2);
	ft_putendl_fd(" arg3 : time_to_eat", 2);
	ft_putendl_fd(" arg4 : time_to_sleep", 2);
	ft_putendl_fd(" arg5 : [opt] number_of_times_each_philosopher_must_eat", 2);
	return (1);
}

void	exit_error(char *e)
{
	ft_perror("Error\n", EXIT_FAILURE);
	ft_perror(e, EXIT_FAILURE);
	exit(ft_perror("\n", EXIT_FAILURE));
}

t_ph	*ft_ph(void)
{
	static t_ph	x = {
		.n_philo = 0
	};

	return (&x);
}

static __attribute__((destructor)) void	ph_destructor(void)
{
}
