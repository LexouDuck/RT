/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fast_inv_sqrt32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:47:23 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/16 14:47:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/*
**	y  = y * (threehalfs - (x2 * y * y));
**		can be repeated for more precision
*/

t_f32		ft_fast_inv_sqrt32(t_f32 f)
{
	long		i;
	t_f32		x2;
	t_f32		y;
	const t_f32	threehalfs = 1.5F;

	x2 = f * 0.5F;
	y = f;
	i = *(long *)(&y);
	i = 0x5f3759df - (i >> 1);
	y = *(t_f32 *)(&i);
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}
