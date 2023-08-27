/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:55:04 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/24 11:58:15 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_lexer_parser(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			exit_error("Character different than digit found");
		i++;
	}
}

static void	ft_semantic(char *arg)
{
	if (!ft_isint(arg) || (ft_atoi(arg) <= 0))
		exit_error("The arg must be an int and bigger than 0");
}

void	ft_analyzer(char **vargs)
{
	int		i;

	i = 1;
	while (vargs[i])
	{
		if (ft_strlen(vargs[i]) == 0)
			exit_error("Empty argument");
		ft_lexer_parser(vargs[i]);
		ft_semantic(vargs[i]);
		i++;
	}
	if (i == 1)
		exit_error("No arguments received");
}
