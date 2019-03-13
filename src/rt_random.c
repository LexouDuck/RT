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

#include "../rt.h"
#include "debug.h"
#include "rt_random.h"

inline t_u32		ft_rand_0_to_pow2n(t_u32 n)
{
	return (ft_rand() & ((0x1 << n) - 1));
}

inline t_u32		ft_rand_0_to_n(t_u32 n)
{
	return (ft_rand() % n);
}

/*
** XOR swap.
*/

inline int			ft_rand_a_to_b(int a, int b)
{
	if (a < b)
		return (ft_rand_0_to_n(b - a) + a);
	else
		return (ft_rand_0_to_n(a - b) + b);
}

inline t_float		ft_frand_0_to_1(void)
{
	return (((t_float)ft_rand()) / MODULUS);
}

/*
** XOR swap.
*/

inline t_float		ft_frand_a_to_b(t_float a, t_float b)
{
	if (a < b)
		return (ft_frand_0_to_1() * (b - a) + a);
	else
		return (ft_frand_0_to_1() * (a - b) + b);
}
