/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_cubic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:37:13 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/25 14:26:49 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "rt.h" //"libft.h"

/*
** https://en.wikipedia.org/wiki/Cubic_function
** https://www.codeproject.com/Articles/798474/To-Solve-a-Cubic-Equation
** 
**
** Context: degree 3 polynomial with real coefficients
** The numbers of real and complex roots are determined by the discriminant
**		of the cubic equation :
**			Δ = 18abcd − 4b^3*d + b^2*c^2 − 4a*c^3 − 27a^2*d^2 
**
**	If Δ > 0, then the equation has three distinct real roots.
**	If Δ = 0, then the equation has a multiple root and all of its roots are
**		real.
**	If Δ < 0, then the equation has one real root and two non-real complex
**		conjugate roots.
**
**	NB: indices: a is 0, b is 1, c is 2, d is 3
*/

static t_float		solve_cubic_get_discriminant(t_vec_4d const cubicpoly)
{
	t_float		delta;
	t_vec_4d	tmp;
	t_float		ad;

	vec4_cpy(tmp, cubicpoly);
	ad = tmp[0] * tmp[3];
	delta = 18 * ad * tmp[1] * tmp[2];
	tmp[1] *= cubicppoly[1];
	tmp[2] *= cubicppoly[2];
	delta += tmp[1] * tmp[2];
	tmp[1] *= cubicppoly[1];
	tmp[2] *= cubicppoly[2];
	delta -= 4 * (tmp[1] * tmp[3] + tmp[0] * tmp[2]);
	delta -= 27 * ad * ad;
	return (delta);
}

/*
** Note that cbrt(float) exists in the <math.h>
*/
