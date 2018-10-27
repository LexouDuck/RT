/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpolynom_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:49:27 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/02 15:50:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_polynomial.h"

t_cpoly		derive_cpoly(t_cpoly poly)
{
	t_cpoly		deriv;
	int			i;

	deriv.deg = poly.deg - 1;
	i = poly.deg;
	while (i > 0)
	{
		deriv.coefs[i - 1] = c_scl((t_float)i, poly.coefs[i]);
		--i;
	}
	return (deriv);
}

/*
** Naive, non-FFT implementation
*/

t_cpoly		cpoly_mul(t_cpoly cp1, t_cpoly cp2)
{
	t_cpoly		convo;
	int			k;
	int			i;
	int			j;

	if (cp1.deg > MAX_DEGREE - cp2.deg)
	{
		convo.deg = write(2, "cpoly_mul: result exceeds max degree\n", 37);
		return (convo);
	}
	ft_bzero(convo.coefs, (convo.deg = cp1.deg + cp2.deg) * sizeof(t_complex));
	k = -1;
	while (++k <= convo.deg)
	{
		i = -1;
		while (++i <= cp1.deg)
		{
			j = -1;
			while (++j <= cp2.deg)
				if (i + j == k)
					convo.coefs[k] = c_add(convo.coefs[k],
											c_mul(cp1.coefs[i], cp2.coefs[j]));
		}
	}
	return (convo);
}

void		roots_to_coefs(t_cpoly *a_cpolymul)
{
	t_cpoly		res;
	t_cpoly		tmp;
	int			i;

	res.deg = 0;
	res.coefs[0].re = 1.;
	res.coefs[0].im = 0.;
	tmp.deg = 1;
	tmp.coefs[1].re = 1.;
	tmp.coefs[1].im = 0.;
	i = a_cpolymul->deg + 1;
	while (--i >= 0)
	{
		tmp.coefs[0] = c_scl(-1., a_cpolymul->coefs[i]);
		res = cpoly_mul(res, tmp);
	}
	*a_cpolymul = res;
}
