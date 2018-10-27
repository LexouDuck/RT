/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:50:21 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:50:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_polynomial.h"

t_float		eval_poly(t_poly const poly, t_float const x)
{
	t_float	result;
	int		i;

	result = 0.;
	i = poly.deg;
	while (i >= 0)
	{
		result = result * x + poly.coefs[i];
		--i;
	}
	return (result);
}

t_float		eval_poly_fast(t_poly *ro_poly, t_float const x)
{
	t_float		result;
	int			i;
	t_float		*coefs;

	result = 0.;
	coefs = ro_poly->coefs;
	i = ro_poly->deg;
	while (i >= 0)
	{
		result = result * x + coefs[i];
		--i;
	}
	return (result);
}

t_float		eval_polyfrac(t_polyfrac const pf, t_float const x)
{
	t_float		num;
	t_float		den;

	num = eval_poly(pf.num, x);
	den = eval_poly(pf.den, x);
	return (num / den);
}

t_float		eval_polyfrac_fast(t_polyfrac *ro_pf, t_float const x)
{
	t_float		num;
	t_float		den;

	num = eval_poly_fast(&(ro_pf->num), x);
	den = eval_poly_fast(&(ro_pf->den), x);
	return (num / den);
}

t_polyfrac	set_polyfrac(t_poly const num, t_poly const den)
{
	t_polyfrac	res;

	res.num = num;
	res.den = den;
	return (res);
}
