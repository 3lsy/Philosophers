/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isull.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:53 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/04 16:21:06 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isull(char *nb)
{
	const char	*ull_max = "18446744073709551615";
	t_ull		tmp;

	if (ft_strlen(nb) > 20)
		return (0);
	if (ft_strlen(nb) < 20)
		return (1);
	if (nb[0] > ull_max[0])
		return (0);
	else if (nb[0] < ull_max[0])
		return (1);
	tmp = ft_atoull(&nb[1]);
	if (tmp > 8446744073709551615)
		return (0);
	return (1);
}
