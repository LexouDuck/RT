/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:32:41 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/04 09:08:04 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

/*
** TODO
** - VLQ,
** - Precomputed list of Powers of 2 and 10 in t_u64, t_s64, double and vlq ?
** - test ln, exp, floor, ceil more extensively.
*/

# include "libft.h"
# include "libft_str.h"

# define DIV1_BY10		0x1.999999999999Ap-4
# define LN2_DIV_LN10	0x1.34413509F79FFp-2
# define LN_3DIV2		0x1.9F323ECBF984Cp-2
# define DIV2_BY3		0x1.5555555555556p-1
# define LN2			0x1.62E42FEFA39EFp-1
# define LN10			0x1.26BB1BBB55516p+1

# define HALF_PI		0x1.921fb54442d18p+0
# define PI				0x1.921fb54442d18p+1
# define TAU 			0x1.921fb54442d18p+2
# define INV_PI			0x1.45f306dc9c883p-2

/*
** # define ABS(X) (X < 0 ? -X : X)
** # define MAX(X, Y) (X < Y ? Y : X)
** # define MIN(X, Y) (X < Y ? X : Y)
*/

/*
** =============== Math Functions ===================
*/

/*
** Returns the distance from x to 0.
*/
t_u64					ft_abs(t_s64 x);

/*
** Returns the floating point distance from x to 0.
*/
t_float					ft_fabs(t_float x);

/*
** Returns max of a and b, signed.
*/
t_s64					ft_max(t_s64 a, t_s64 b);

/*
** Returns min of a and b, signed.
*/
t_s64					ft_min(t_s64 a, t_s64 b);

/*
** Returns max of a and b, unsigned.
*/
t_u64					ft_umax(t_u64 a, t_u64 b);

/*
** Returns min of a and b, unsigned.
*/
t_u64					ft_umin(t_u64 a, t_u64 b);

/*
** Returns max of a and b, floating point.
*/
t_float					ft_fmax(t_float a, t_float b);

/*
** Returns min of a and b, floating point.
*/
t_float					ft_fmin(t_float a, t_float b);

/*
** Returns closest int closer to -inf than lf. Prints error messages in case of
** litigious cases.
*/
long					ft_floor(double lf);

/*
** Returns closest int closer to +inf than lf.
*/
long					ft_ceil(double lf);

/*
** Returns the power to which 2 must be raised to obtain pow_of_2. If the number
** given is not a positive power of 2, returns -1.
*/
int						ft_ilog2(t_u64 pow_of_2);

/*
** Returns an int to the power of a uint, checking for overflow.
*/
t_u64					ft_ipowi(t_u32 x, t_u8 pow);

/*
** Returns a double to the power of an int, without checking for overflow.
** Handles negative powers.
*/
double					ft_lfpowi(double x, int pow);

/*
** Returns the exponential of lf. Uses Taylor expansion.
*/
double					ft_exp(double x);

/*
** Returns the natural logarithm of lf, using the Taylor expansion to build
** precision up to decim_prec.
*/
double					ft_ln(double lf);

/*
** Returns the base 'n' logarithm of lf, using the Taylor expansion to build
** precision up to decim_prec.
*/
double					ft_logn(double lf, double n);

/*
** Returns true is if x is in the closed interval [start; end].
*/
t_bool					ft_float_in_interval(t_float x,
									t_float start, t_float end);

/*
** ========== Str-Int Conversion Functions ==========
*/

/*
** Returns the number of digits in n knowing that n is written in base 10.
*/
int						ft_digits(intmax_t n);

/*
** Returns the number of digits in n knowing that n is written in base "base".
** n is signed.
*/
int						ft_digits_base(intmax_t n, int base);

/*
** Returns the number of digits in n knowing that n is written in base "base".
** n is unsigned.
*/
int						ft_udigits_base(uintmax_t n, int base);

/*
** Returns an int parsed from the given string number 'str' (returns 0 if
** 'str' is invalid).
*/
int						ft_atoi(char const *str);

/*
** Returns a long parsed from the given string number 'str', according to the
** given 'base' (returns 0 if 'str' is invalid). DOES NOT CHECK FOR LONG
** OVERFLOW.
*/
long					ft_atoi_base(char const *str, char const *base);

/*
** Returns an unsigned long parsed from the given string number 'str',
** according to the given 'base' (returns 0 if 'str' is invalid). DOES NOT
** CHECK FOR LONG OVERFLOW.
*/
t_u64					ft_atoui_base(char const *str, char const *base);

/*
** Returns a new string which is the representation of the given number 'n'.
*/
char					*ft_itoa(long n);

/*
** Returns a new string which is the representation of the given number 'n',
** according to the given 'base'.
*/
char					*ft_itoa_base(long nb, char const *base);

/*
** itoa with longer arg.
*/
char					*ft_imaxtoa_base(intmax_t nb, const char *base);

/*
** Returns a new string which is nb written in "base" where nb is unsigned.
*/
char					*ft_uitoa_base(unsigned long nb, char const *base);

/*
** uitoa_base with longer arg.
*/
char					*ft_uimaxtoa_base(uintmax_t nb, const char *base);

/*
** Returns lf as a string with maximum precision (full conversion) with style
** convention: 'p' for hexfp, 'e' for exponential, '\0' for floating point
*/
char					*ft_lftoa(double lf, char style);

/*
** Uses presence of p and of at least 1 e to ascertain the format of a given
** float between hexfp %a, scientific %e, and decimal %f and returns a double
** accurate up to "least_precise(input str prec, machine prec)".
*/
t_f64					ft_atolf(char const *float_str);

/*
** Takes a string as a number written in base "base_from" (digit val == index
** of digit symbol in string) and returns a newly allocated (itoa_base) string
** in base "base_to", passing the argument through a long int.
*/
char					*ft_convert_base(char const *nbr,
										char const *base_from,
										char const *base_to);

/*
** Takes a string as a number written in base "base_from" (digit val == index
** of digit symbol in string) and returns a newly allocated (itoa_base) string
** in base "base_to", passing the argument through an unsigned long int.
*/
char					*ft_uconvert_base(char const *nbr,
										char const *base_from,
										char const *base_to);

/*
** Returns 1 if base contains only distinct symbols and contains only printable
** characters. Returns 0 otherwise, or if '+' or '-' are used as symbols in
** base.
*/
int						ft_is_valid_base(char const *base);

/*
** Returns true iff base is a valid base and nbstr can be read in base.
*/
t_u8					ft_is_valid_nbstr_in_base(char const *nbstr,
													char const *base);

/*
** Returns the index of c in base, which is also its digit value. Inputting '\0'
** for c returns strlen, absence of c in base returns -1.
*/
int						ft_in_base(char c, char const *base);

/*
** Returns an approximation of the inverse square root of a number.
** More precision can be had with 1./sqrt() if necessary.
**
** t_f32					ft_fast_inv_sqrt32(t_f32 const f);
*/
#endif
