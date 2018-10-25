/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:56:42 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:14:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

double		ft_exp(double x)
{
	double	i;
	double	acc_i;
	double	acc_x;
	double	result;
	double	prev_res;

	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	prev_res = 0.;
	while (result != prev_res)
	{
		prev_res = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
}
