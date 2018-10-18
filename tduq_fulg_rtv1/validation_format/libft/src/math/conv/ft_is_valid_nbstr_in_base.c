/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_nbstr_in_base.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:31:27 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_u8		ft_is_valid_nbstr_in_base(char const *nbstr, char const *base)
{
	t_u32		i;

	if (!nbstr || !ft_is_valid_base(base))
		return (0);
	i = (nbstr[0] == '+' || nbstr[0] == '-');
	while (nbstr[i])
	{
		if (ft_in_base(nbstr[i], base) == -1)
			return (0);
		++i;
	}
	return (1);
}
