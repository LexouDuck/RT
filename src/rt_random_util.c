/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_random_util.c                                   :+:      :+:    :+:   */
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

t_u32				ft_srand(t_u32 seed)
{
	g_rt.random_value = DEFAULT_SEED * seed;
	return (g_rt.random_value);
}

t_u32				ft_rand(void)
{
	g_rt.random_value = CEIL_SQRT_MOD * ft_rand_bit_shuffle(g_rt.random_value);
	g_rt.random_value += OFFSET;
	g_rt.random_value &= MODULUS;
	return (g_rt.random_value);
}
