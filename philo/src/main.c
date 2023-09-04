/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:43:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/01 20:13:11 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_usage(void)
{
	ft_putendl_fd("There must be 4 to 5 arguments", 2);
	ft_putendl_fd("Usage: ./philo arg1 arg2 arg3 arg4 [arg5]", 2);
	ft_putendl_fd("In which:", 2);
	ft_putendl_fd(" arg1 : number_of_philosophers", 2);
	ft_putendl_fd(" arg2 : time_to_die", 2);
	ft_putendl_fd(" arg3 : time_to_eat", 2);
	ft_putendl_fd(" arg4 : time_to_sleep", 2);
	ft_putendl_fd(" arg5 : [opt] number_of_times_each_philosopher_must_eat", 2);
}

void	ft_destructor(t_ph *ph)
{
	if (ph)
	{
		pthread_mutex_destroy(&ph->data_meal);
		if (ph->philo)
			free(ph->philo);
		if (ph->forks)
			ph = destroy_forks(ph);
		if (ph->ids)
			free(ph->ids);
		if (ph->stomach_full)
			free(ph->stomach_full);
	}
}

void	exit_error(char *e, t_ph *ph)
{
	ft_destructor(ph);
	ft_perror("Error\n", EXIT_FAILURE);
	ft_perror(e, EXIT_FAILURE);
	exit(ft_perror("\n", EXIT_FAILURE));
}

int	main(int ac, char **av)
{
	t_ph	*ph;
	int		i;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		ph = ft_arg_parser(av);
		ph = create_forks(ph);
		ph = create_philosophers(ph);
		pthread_mutex_init(&ph->data_meal, NULL);
		pthread_mutex_init(&ph->data_stomach, NULL);
		pthread_create(&ph->lamuerte, NULL, lamuerte, (void *)ph);
		while (i < ph->n_philo)
			pthread_join(ph->philo[i++], NULL);
		pthread_join(ph->lamuerte, NULL);
		ft_destructor(ph);
		return (EXIT_SUCCESS);
	}
	ft_usage();
	return (EXIT_FAILURE);
}
