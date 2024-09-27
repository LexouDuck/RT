/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_getpow2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:09:12 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Returns 2^exp2 as a vlq.
*/

t_vlq			ft_vlq_getpow2(t_u32 exp2)
{
	t_vlq		result;
	t_u32		arr_size;
	t_u8		bit_pos;
	t_u32		i;

	arr_size = (exp2 / 63) + 1;
	bit_pos = exp2 % 63;
	result = ft_vlqnew(arr_size);
	result[0] = (arr_size > 1 ? _MSB_ : 0) | (0x1 << bit_pos);
	i = 1;
	while (i < arr_size - 1)
	{
		result[i] = _MSB_;
		++i;
	}
	result[i] &= _MSB_;
	return (result);
}
