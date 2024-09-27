/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_complex.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 02:25:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/15 02:25:59 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COMPLEX_H
# define LIBFT_COMPLEX_H

# include <math.h>
# include "libft_math.h"

typedef struct	s_complex
{
	t_float		re;
	t_float		im;
}				t_complex;

typedef struct	s_complex_pol
{
	t_float		rad;
	t_float		arg;
}				t_complex_pol;

t_complex		c_add(t_complex const z1, t_complex const z2);
t_complex		c_scl(t_float const s, t_complex const z);
t_complex		c_mul(t_complex const z1, t_complex const z2);
t_complex		c_inv(t_complex const z);
t_float			c_quadnorm(t_complex const z);

/*
** TODO
**
** t_complex_pol	cpol_mul(t_complex_pol const ra1, t_complex_pol const ra2);
** t_complex_pol	cpol_pow(t_complex_pol const radarg, t_float const expon);
** t_complex_pol cpol_cpow(t_complex_pol const radarg, t_complex const expon);
**
** t_complex_pol		c_cart_to_exp(t_complex const z);
** t_complex		c_exp_to_cart(t_complex_pol const radarg);
** t_complex		cpol_mul(t_complex z1, t_complex z2);
**
** TODO
** => accumulator functions
*/
#endif
