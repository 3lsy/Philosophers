/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:43:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/12 11:15:18 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 5 || ac == 6)
	{
		return (0);
	}
	ft_putendl_fd("Error", 1);
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
	};

	return (&x);
}

static __attribute__((destructor)) void	ph_destructor(void)
{
}
