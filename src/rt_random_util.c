/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_random.h"

#include "../rt.h"
#include "debug.h"

inline static t_u32	ft_rand_bit_shuffle(t_u32 n)
{
	return ((n << 12) ^ (n >> 20));
}

t_u32				ft_srand(int mode, t_u32 value)
{
	static t_u32	new_nb = DEFAULT_SEED;

	if (mode == 1)
		new_nb *= rt.sdl.current_frame;
	if (mode == 2)
		new_nb = value;
	return (new_nb);
}

t_u32				ft_rand(void)
{
	t_float		new_nb;

	new_nb = (CEIL_SQRT_MOD * ft_rand_bit_shuffle(new_nb) + OFFSET) & MODULUS;
	ft_srand(2, new_nb);
	return (new_nb);
}
