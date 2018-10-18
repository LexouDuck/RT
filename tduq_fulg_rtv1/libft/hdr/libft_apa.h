/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_apa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 05:44:23 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/25 19:29:17 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_APA_H
# define LIBFT_APA_H

# include "libft.h"
# include "libft_mem.h"
# include "libft_math.h"
# include "libft_io.h"

/*
** TODO
** - Maybe add more checks that the first element of a vlq should be different
** from	_MSB_ ?
** - Maybe refactor NOT_MSB as OPP_MSB to avoid confusion for !NOT_MSB checks
** - Refactor bsl to bsl and bsr to bsr and inplace to acc for coherence
** - make more optimized bwa_acc and bwo_acc operators.
** - floating point arbitrary precision type, with appropriate operators.
** - Change the convention for the length of a vlq from t_u32 to t_u16 or t_u8 ?
** - optimize base conversion through a vlq_divmod function which we call with
**		radix^n where n is the largest power to which radix can be raised before
**		unsigned long overflow. It's that or Dragon4...
** - debug display and coherence checker for bignb ?
*/

# ifndef __BASES__
#  define __BASES__
#  define BINAR "01"
#  define OCTAL "01234567"
#  define DECIM "0123456789"
#  define HXLOW "0123456789abcdef"
#  define HXUPP "0123456789ABCDEF"
# endif

/*
** Variable Length Quantity (Very Long Unsigned Integer)
**
** Our VLQs are made to be used as follows:
**	- Dynamically allocated.
**	- Every number is used as its absolute (positive) value (the bignb type
**		below handles signs in its operations.
** 	- Every non-terminating t_u64 of the array starts with its MSB == 1 ;
**		the last allocated index in the array starts with its MSB == 0.
**	- The actual abstract value represented is in binary, where for each t_u64,
**		the remaining 63 bits are concatenated to represent it. LSB of the full
**		value must coincide with the LSB of the terminating t_u64. If the
**		array's LSB is 0, this is to signify a power of at least two.
**	- u64 with MSB == 0 can be recognized as t_vlq by address; behavior for
**		any t_u64 > 2^63 or negative signed longs is undefined.
**
** # define MSB(x) 		((x) >> 63)
** # define NOT_MSB(x) 	((x) & _NOT_MSB_)
*/

typedef t_u64*	t_vlq;

/*
** ============= VLQ functions ============
**
** Since VLQs are strictly positive, all functions work with them being so.
** is_zero is unnecessary as it suffises to check vlq[0] == 0 for well-formed
** vlqs.
*/

/*
** ~~~~~~~~~ VLQ Utils ~~~~~~~~~~
*/

/*
** Returns a u64 array of size 'size', with every leading bit set to work with
** the VLQ format. To set a value in an index, use "result[i] |= NOT_MSB(ul);"
*/
t_vlq			ft_vlqnew(t_u32 size);

/*
** Returns a newly-allocated copy of the vlq.
*/
t_vlq			ft_vlqdup(t_vlq const vlq);

/*
** Makes a VLQ from a string representing a number in a given base.
** 		- nbstr in input is to be given normal order, not rev.
** 		- leading + and - are ignored; internal + and - cause error.
*/
t_vlq			ft_atovlq(char const *nbstr, char const *base);

/*
** Returns the difference in array size or the difference within the chunk to
** function like other cmp function (ie, vlq1 < vlq2 <=> cmp(vlq1, vlq2) < 0)
*/
long			ft_vlqcmp(t_vlq const vlq1, t_vlq const vlq2);

/*
** Returns the length of a given vlq.
*/
t_u32			ft_vlqlen(t_vlq const vlq);

/*
** Returns the power to which two must be raised to obtain the leading bit of
** the actual value contained in the t_vlq.
*/
t_u32			ft_vlq_log2(t_vlq const vlq);

/*
** Returns a newly allocated vlq with a single bit set to 1 (other than the
** MSBs' 1s which allow for null-termination) at the appropriate position
** for the return value to be equal to pow(2, exp).
*/
t_vlq			ft_vlq_getpow2(t_u32 exp);

/*
** Returns a newly allocated vlq == pow(10, exp). Only accepts exponents up to
** 511.
*/
t_vlq			ft_vlq_getpow10(t_u32 exp);

/*
** Returns a string in 'base' representing the value vlq.
*/
char			*ft_vlqtoa_base(t_vlq const vlq, char const *base);

/*
** Counts the minimal number one must give a right shift to send vlq_p to zero,
** ignoring the format MSB.
*/
t_u8			ft_vlq_count_sigbit_of_part(t_u64 vlq_p);

/*
** Returns the number of significant bits in our whole vlq, or 0 if the vlq
** is improperly formatted. The number 0 has 1 significant bit.
*/
t_u32			ft_vlq_count_sigbit(t_vlq vlq);

/*
** Returns a string of all the u64 in a vlq, as they are (with MSB) in 0xHXLOW.
*/
char			*ft_vlqhex(t_vlq const vlq);

/*
** Returns the abstract value represented by vlq as a string of hexadecimal
** digits.
*/
char			*ft_vlq_abstractval_as_hex(t_vlq const vlq);

/*
** Returns the vlq without its leading zeros. This version reallocates to avoid
** future problems with free on *a_vlq.
*/
void			ft_vlqtrim(t_vlq *a_vlq);

/*
** Checks if vlq is allocated, if so, cleans and frees memory.
*/
void			ft_vlqdel(t_vlq *a_vlq);

/*
** ~~~~~~~~~ VLQ operators ~~~~~~~~~
*/
/*
** Returns a + b.
*/
t_vlq			ft_vlq_add(t_vlq const a, t_vlq const b);

/*
** Returns ABS(a - b).
*/
t_vlq			ft_vlq_sub(t_vlq const a, t_vlq const b);

/*
** Returns a * b.
*/
t_vlq			ft_vlq_mul(t_vlq const a, t_vlq const b);

/*
** Returns a / b.
*/
t_vlq			ft_vlq_div(t_vlq const a, t_vlq const b);

/*
** Returns a / b and a % b through pointers.
*/
void			ft_vlq_divmod(t_vlq const a, t_vlq const b,
							t_vlq *div, t_vlq *mod);

/*
** Returns vlq multiplied by 2^shift.
*/
t_vlq			ft_vlq_bsl(t_vlq const vlq, t_u32 shift);

/*
** Returns vlq (euclidean) divided by 2^shift.
*/
t_vlq			ft_vlq_bsr(t_vlq const vlq, t_u32 shift);

/*
** Returns (a & b) then trims if needed.
**
** t_vlq			ft_vlq_bwa(t_vlq const a, t_vlq const b);
*/

/*
** Returns (a | b).
**
** t_vlq			ft_vlq_bwo(t_vlq const a, t_vlq const b);
*/

/*
** Uses exponentiation by squares to return a ^ exp.
*/
t_vlq			ft_vlq_pow(t_vlq const a, t_vlq exp);

/*
** Replaces 'acc' with the value a + b.
*/
void			ft_vlq_add_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces 'acc' with the value ABS(a - b).
*/
void			ft_vlq_sub_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces 'acc' with the value a * b.
*/
void			ft_vlq_mul_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces 'acc' with the value a / b.
*/
void			ft_vlq_div_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces vlq with the value "vlq multiplied by 2^shift".
*/
void			ft_vlq_bsl_acc(t_vlq *vlq, t_u32 shift);

/*
** Replaces vlq with the value "vlq (euclidian) divided by 2^shift".
*/
void			ft_vlq_bsr_acc(t_vlq *vlq, t_u32 shift);

/*
** Returns 10^exp10 as a vlq. Inspiration taken from Dragon4 for speed.
*/
t_vlq			ft_vlq_getpow10(t_u32 exp10);

/*
** Returns returns the value res = 10^n <= vlq < 10^(n+1) as a vlq.
*/
t_vlq			ft_vlq_get_greatest_sub_pow10(t_vlq const vlq);

/*
** TODO bwa bwa_acc bwo bwo_acc
*/

/*
** Very Long Float / Variable length float
**
** Abstract value represented = mantissa[2] * 2 ^ exp_b2[2]
**		this means exp_b2 <=> movements of floating point
**
**	- 	mantissa :	all significant digits in binary as a vlq; the point is
**					  considered to be set after the LSB of the abstract value.
**	-	exp_b2 :	the movement of the floating point; a negative value n is a
**					  bitshift right with appropriate understanding of the
**					  fractional parts in the vlf_ops(); a positive value is a
**					  bitshift left (appendding zeros);
**	-	neg :		true if vlf < 0, false otherwise.
*/

typedef struct	s_vlf
{
	t_vlq			mantissa;
	int				exp_b2;
	t_u32			neg;
}				t_vlf;

/*
** =========== VLF Functions ==========
*/
/*
** TODO
**
** div = mul by inverse ? If so, how does one compute the inverse ? Make sure
** to warn if infinite fraction !
*/
#endif
