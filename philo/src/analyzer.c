/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:55:04 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/12 17:08:39 by echavez-         ###   ########.fr       */
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

void	ft_analyzer(char **vargs)
{
	int		i;

	i = 1;
	while (vargs[i])
	{
		if (ft_strlen(vargs[i]) == 0)
			exit_error("Empty argument");
		ft_lexer_parser(vargs[i]);
		i++;
	}
	if (i == 1)
		exit_error("No arguments received");
}
