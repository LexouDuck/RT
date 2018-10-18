/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 06:05:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/*
** Returns the power to which n should be raised to obtain lf.
*/

double		ft_logn(double lf, double n)
{
	double	ln_base;

	ln_base = n == 10 ? LN10 : ft_ln(n);
	return (ft_ln(lf) / ln_base);
}
