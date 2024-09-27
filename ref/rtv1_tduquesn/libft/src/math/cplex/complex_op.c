/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:23:45 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/16 14:26:15 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_complex.h"

t_complex		c_add(t_complex const z1, t_complex const z2)
{
	t_complex	res;

	res.re = z1.re + z2.re;
	res.im = z1.im + z2.im;
	return (res);
}

t_complex		c_scl(t_float const s, t_complex const z)
{
	t_complex	res;

	if (s == -1.)
	{
		res.re = -z.re;
		res.im = -z.im;
	}
	else if (s == 0.)
	{
		res.re = 0.;
		res.im = 0.;
	}
	else
	{
		res.re = s * z.re;
		res.im = s * z.im;
	}
	return (res);
}

/*
** Karatsuba
*/

t_complex		c_mul(t_complex const z1, t_complex const z2)
{
	t_complex	res;
	t_float		k1;
	t_float		k2;
	t_float		k3;

	k1 = z2.re * (z1.re + z1.im);
	k2 = z1.re * (z2.im - z2.re);
	k3 = z1.im * (z2.re + z2.im);
	res.re = k1 - k3;
	res.im = k1 + k2;
	return (res);
}

inline t_float	c_quadnorm(t_complex const z)
{
	return (z.re * z.re + z.im * z.im);
}

t_complex		c_inv(t_complex const z)
{
	t_complex	res;
	t_f32		inv_norm;

	inv_norm = 1. / sqrt(c_quadnorm(z));
	res.re = inv_norm * z.re;
	res.im = -inv_norm * z.im;
	return (res);
}
