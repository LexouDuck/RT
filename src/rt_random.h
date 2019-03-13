/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_random.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_RANDOM_H
# define __RT_RANDOM_H

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

/*
** ************************************************************************** *|
**                                  Includes                                  *|
** ************************************************************************** *|
*/

# include "libft.h"

# include "rt_cl.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef enum	e_random_type
{
	TYPE_FLOAT = 0,
	TYPE_PRIMITIVE,
	TYPE_MATERIAL,
	TYPE_COLOR,
	TYPE_BBOX,
	TYPE_POS_X,
	TYPE_POS_Y,
	TYPE_POS_Z,
}				t_random_type;

void			write_float3(int fd, char *label, t_random_type type);
void			write_enums(int fd);
void			write_bgcolor(int fd);
int				set_alea_nb(t_random_type type);
cl_float3		set_float3_nb(t_random_type type);

int				rt_auto_build_scene(char *filename);
void			rt_auto_build_cornellbox(int fd);

# define DEFAULT_SEED	0xCAF3DEC4

# define MODULUS		0x7FFFFFFF
# define CEIL_SQRT_MOD	46341
# define OFFSET			2835

t_u32			ft_rand(void);
t_u32			ft_rand_0_to_pow2n(t_u32 n);
t_u32			ft_rand_0_to_n(t_u32 n);
int				ft_rand_a_to_b(int a, int b);
t_u32			ft_srand(t_u32 seed);
t_float			ft_frand_0_to_1(void);
t_float			ft_frand_a_to_b(t_float a, t_float b);

#endif
