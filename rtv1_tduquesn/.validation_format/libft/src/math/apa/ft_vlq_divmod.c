/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_divmod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:37:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Returns which vlq's abstract value would come first in a binary-alphabet-
** based dictionary (not reversed). cmp conventions applied, ie, return < 0 iff
** a < b in binary lexicographic order iff a precedes b in the bin dictionary.
**
** TODO: if unstatic, change diff argument and commented values
** //	int		diff;
** //	diff = ft_vlq_count_sigbit(a) - ft_vlq_count_sigbit(b);
*/

static long		ft_vlqlexcmp(t_vlq const a, t_vlq const b, int diff)
{
	long	result;
	t_vlq	tmp;

	if (diff == 0)
		result = ft_vlqcmp(a, b);
	else if (diff < 0)
	{
		tmp = ft_vlq_bsl(a, -diff);
		result = ft_vlqcmp(tmp, b);
		ft_vlqdel(&tmp);
	}
	else
	{
		tmp = ft_vlq_bsl(b, diff);
		result = ft_vlqcmp(a, tmp);
		ft_vlqdel(&tmp);
	}
	return (result);
}

/*
** Returns the number of trailing zeros in the astract binary value of vlq.
*/

static t_u32	ft_vlq_is_pow2_divisible(t_vlq const vlq)
{
	t_u32	pow2;
	t_s32	i;
	t_s8	j;

	if (!ft_not_msb(vlq[0]))
		return (0);
	pow2 = 0;
	i = ft_vlqlen(vlq);
	while (--i >= 0)
	{
		j = 0;
		while (j < 63)
		{
			if ((vlq[i] >> j) % 2)
				return (pow2);
			++pow2;
			++j;
		}
	}
	return (pow2);
}

/*
** 'ops % 63' is the sigbits of res_q[0] because ops == quo_sigbits,
** 'cbi' current absolute (abstract value) vlq bit index of res_q
** '63 - sigbits' is the 0s before these sigbits, called vlqmsb_offset elsewhere
** '++cbi' with each new operation,
** 'cbi / 63' is to get the index from the bitindex inside the vlq,
**		given by ((63 - (ops % 63)) % 63) + i)
**
** TODO verify usage of extra to make sure
*/

static t_vlq	do_vlqdiv(t_vlq *tmp_n, t_vlq *tmp_d, t_u32 ops)
{
	t_vlq	res_q;
	long	i;
	t_u32	cbi;
	t_u8	extra;

	ft_vlq_bsl_acc(tmp_d, ops - 1);
	res_q = ft_vlqnew((ops / 63) + 1);
	cbi = (63 - (ops % 63));
	i = 0;
	while (i < ops && **tmp_n != 0)
	{
		extra = 1;
		if (ft_vlqcmp(*tmp_n, *tmp_d) >= 0)
		{
			ft_vlq_sub_acc(tmp_n, *tmp_d);
			extra += cbi % 63;
			res_q[cbi / 63] |= ft_u64bits_itoj(_ALLBITS_, extra, extra + 1);
			extra = ft_vlq_count_sigbit(*tmp_d) - ft_vlq_count_sigbit(*tmp_n);
			extra = extra == 0 ? 1 : extra;
		}
		ft_vlq_bsr_acc(tmp_d, extra);
		cbi += extra;
		i += extra;
	}
	return (res_q);
}

static int		divmod_init_checks(t_vlq const num, t_vlq const den,
							t_vlq *div, t_vlq *mod)
{
	if (!div || num[0] == _MSB_ || !ft_not_msb(den[0]))
	{
		ft_putendl_fd("Improper vlq operand or division by 0 in vlq_div.", 2);
		return (1);
	}
	if (ft_vlqcmp(num, den) < 0)
	{
		*div = ft_vlqnew(1);
		*mod = mod ? ft_vlqdup(num) : NULL;
		return (1);
	}
	return (0);
}

/*
** https://gmplib.org/manual/Division-Algorithms.html#Division-Algorithms
** Our algorithm uses wwltc "fundamental theorem of binary": that any positive
** integer can be expressed as a sum of powers of two. It's like what we did
** using addition for multiplication, but with subtraction instead.
**
** We also though of an iterative approach which estimates the quotient in
** chunks by using register division on indices of the vlq, shifting left then
** multiplying this quotient by the denominator, comparing to see if it's still
** under the numerator, then if it's the largest multiple of den below num,
** substracting it from num and keeping the appropriate operand as new bits in
** our quotient, thus gradually reducing the numerator while obtaining the
** solution.
**
** "num_after_den = (ft_vlqlexcmp(num, den, diff) >= 0)" => if num is after den
** binary-lexicographically, then when you stick the two input numbers correctly
** with matching leading bits, num is superior to den, so there should be one
** more quotient making operation than otherwise.
*/

void			ft_vlq_divmod(t_vlq const num, t_vlq const den,
							t_vlq *div, t_vlq *mod)
{
	t_vlq	tmp_n;
	t_vlq	tmp_d;
	t_u32	quo_sigbits;
	int		diff;
	t_u32	end_0s;

	if (divmod_init_checks(num, den, div, mod))
		return ;
	diff = ft_vlq_count_sigbit(num) - ft_vlq_count_sigbit(den);
	quo_sigbits = ft_abs(diff) + (ft_vlqlexcmp(num, den, diff) >= 0);
	end_0s = ft_min(ft_vlq_is_pow2_divisible(num),
					ft_vlq_is_pow2_divisible(den));
	tmp_n = ft_vlq_bsr(num, end_0s);
	tmp_d = ft_vlq_bsr(den, end_0s);
	*div = do_vlqdiv(&tmp_n, &tmp_d, quo_sigbits);
	ft_vlqtrim(div);
	*mod = (mod) ? ft_vlq_bsl(tmp_n, end_0s) : NULL;
	ft_vlqdel(&tmp_n);
	ft_vlqdel(&tmp_d);
}
