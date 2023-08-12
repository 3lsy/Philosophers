/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:36:52 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/12 20:03:43 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isint(char *nb)
{
	int	i;
	int	pos;

	if (ft_strcmp(nb, "-") == 0)
		return (1);
	pos = (nb[0] != '-');
	if ((int)ft_strlen(nb) < 11 - pos)
		return (1);
	if ((int)ft_strlen(nb) > 11 - pos)
		return (0);
	if (nb[1 - pos] < 50)
		return (1);
	if (nb[1 - pos] > 50)
		return (0);
	if (nb[2 - pos])
	{
		i = ft_atoi(&nb[2 - pos]);
		if (i > 147483648 - pos)
			return (0);
	}
	return (1);
}
