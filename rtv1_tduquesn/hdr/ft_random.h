/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 04:00:36 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/03 19:33:04 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_H
# define FT_RANDOM_H

/*
** Random number generator. Modulus is 2^31
**
** - OFFSET and MODULUS are mutually prime.
** - CEIL_SQRT_MOD % 4 should be = 1 because MODULUS is a multiple of 4
** - For all P prime divisors of MODULUS, a % p = 1
** - OFFSET should be small compared to the two other parameters
** - The bitwise & is applied, which explains the choice of modulus to be
**		2^31 - 1 in implementation (could also be called RAND_MAX)
**
** Basic RNG formula is:
**		new_nb = (CEIL_SQRT_MOD  * old_nb + OFFSET) % MODULUS
*/

#include "../libft/hdr/libft.h"

# define DEFAULT_SEED	0x93E21FD5 //make a global and build an ft_srand ?

# define MODULUS		0x7FFFFFFF		
# define CEIL_SQRT_MOD	46341
# define OFFSET			2835

t_u32		ft_rand(void);
t_u32		ft_rand_0_to_pow2n(t_u32 n);
t_u32		ft_rand_0_to_n(t_u32 n);
t_int		ft_rand_a_to_b(t_int a, t_int b);
t_float		ft_frand_0_to_1(void);
t_float		ft_frand_a_to_b(t_float a, t_float b);

#endif
