/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 04:12:35 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/01 21:43:06 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_random.h"




t_u32 ft_abs(int a) { return a < 0 ? -a : a;}




inline static t_u32	ft_rand_bit_shuffle(t_u32 n)
{
	return ((n << 12) ^ (n >> 20));
}

inline t_u32		ft_rand(void)
{
	static t_u32	new_nb = DEFAULT_SEED;

	new_nb = (CEIL_SQRT_MOD * ft_rand_bit_shuffle(new_nb) + OFFSET) & MODULUS;
	return (new_nb);
}

inline t_u32		ft_rand_0_to_pow2n(t_u32 n)
{
	return (ft_rand() & ((0x1 << n) - 1));
}

inline t_u32		ft_rand_0_to_n(t_u32 n)
{
	return (ft_rand() % n);
}

inline t_int		ft_rand_a_to_b(t_int a, t_int b)
{
	return (ft_rand_0_to_n(ft_abs(b - a)) + a);
}

inline t_float		ft_frand_0_to_1(void)
{
	return (((t_float)ft_rand()) / MODULUS);
}

inline t_float		ft_frand_a_to_b(t_float a, t_float b)
{
	return (ft_frand_0_to_1() * (b - a) + a);
}
