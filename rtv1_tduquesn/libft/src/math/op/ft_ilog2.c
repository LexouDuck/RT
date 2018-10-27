/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilog2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 03:16:52 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:14:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/*
** Returns the power to which 2 must be raised to obtain pow_of_2. If the number
** given is not a positive power of 2, then it returns -1.
*/

int		ft_ilog2(t_u64 pow_of_2)
{
	int		i;

	if (pow_of_2 == 0)
		return (-1);
	i = 0;
	while (pow_of_2 >> 1)
	{
		if (pow_of_2 % 2)
			return (-1);
		pow_of_2 >>= 1;
		++i;
	}
	return (i);
}
