/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_polynomial.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:55:53 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:56:03 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_POLYNOMIAL_H
# define LIBFT_POLYNOMIAL_H

# include "libft_math.h"
# include "libft_complex.h"

/*
** Note that some functions use coefs to denote the roots of a polynomial.
** In this context, the usual "poly" variable name is replaced by "polymul"
** in reference to the multiplicative form of the FToA
*/

# define MAX_DEGREE		32

typedef struct	s_poly
{
	t_u8			deg;
	t_float			coefs[MAX_DEGREE + 1];
}				t_poly;

typedef struct	s_polyfrac
{
	t_poly			num;
	t_poly			den;
}				t_polyfrac;

typedef struct	s_cpoly
{
	t_u8			deg;
	t_complex		coefs[MAX_DEGREE + 1];
}				t_cpoly;

typedef struct	s_cpolyfrac
{
	t_cpoly			num;
	t_cpoly			den;
}				t_cpolyfrac;

t_float			eval_poly(t_poly const poly, t_float const x);
t_float			eval_poly_fast(t_poly *a_poly, t_float const x);
t_float			eval_polyfrac(t_polyfrac const pf, t_float const x);
t_float			eval_polyfrac_fast(t_polyfrac *ro_pf, t_float const x);
t_polyfrac		set_polyfrac(t_poly const num, t_poly const den);

t_complex		eval_cpoly(t_cpoly const cpoly, t_complex const z);
t_complex		eval_cpoly_fast(t_cpoly *a_cpoly, t_complex const z);
t_complex		eval_cpolyfrac(t_cpolyfrac const pf, t_complex const z);
t_complex		eval_cpolyfrac_fast(t_cpolyfrac *ro_cpf, t_complex const z);
t_cpolyfrac		set_cpolyfrac(t_cpoly const num, t_cpoly const den);

t_poly			polyobj_to_poly(char const *str);
char			*poly_to_str(t_poly *ro_poly);

t_cpoly			polyobj_to_cpoly(char const *str);
char			*cpoly_to_str(t_cpoly *ro_cpoly);
char			*cpoly_to_polyobj(t_cpoly *ro_cpoly);
char			*cpolyfrac_to_str(t_cpolyfrac *ro_cpf);

/*
** cpolynom_calc.c
**
** TODO
** derive_poly
** integrate_poly
** integrate_cpoly
*/
t_cpoly			derive_cpoly(t_cpoly cpoly);
t_cpoly			cpoly_mul(t_cpoly cp1, t_cpoly cp2);
/*
** Turns a polynomial interpreted as being in multiplicative form as one
** being interpreted as being in additive form, in place.
*/
void			roots_to_coefs(t_cpoly *a_cpolymul);

#endif
