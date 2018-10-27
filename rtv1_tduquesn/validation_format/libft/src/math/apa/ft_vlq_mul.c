/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:36:39 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Returns -2 if input is improper, or if it is 0. Returns -1 if the input is
** valid but not a power of two.
** Usage is to make sure that if (res >= 0), then input was 2^res.
**
** First part check if there is an active bit in the u64 where the MSB of the
**		abstract value is contained.
** Second part checks if there is an active bit in the rest of the vlq array.
*/

static int		ft_vlq_ispow2(t_vlq const vlq)
{
	t_u32	len;
	t_u32	len2;
	t_u32	i;
	int		pow;

	if (!ft_not_msb(vlq[0]))
		return (-2);
	len = ft_vlq_count_sigbit_of_part(vlq[0]) - 1;
	i = 0;
	while (i < len)
	{
		if ((vlq[0] >> i) % 2 == 0x1)
			return (-1);
		++i;
	}
	len2 = ft_vlqlen(vlq);
	i = 1;
	while (i < len2)
	{
		if (ft_not_msb(vlq[i]))
			return (-1);
		++i;
	}
	pow = len + 63 * (len2 - 1);
	return (pow);
}

/*
** Returns the number of '1' bits in a vlq. Returns 0 in case of zero or
** invalid vlq format.
*/

static t_u32	ft_vlq_count_active_bits(t_vlq const vlq)
{
	t_u32	bits;
	t_u32	len;
	t_u32	i;
	t_s8	j;

	len = ft_vlqlen(vlq);
	bits = 0;
	i = 0;
	while (i < len)
	{
		j = -1;
		while (++j < 63)
			if ((ft_not_msb(vlq[i]) >> j) % 2)
				++bits;
		++i;
	}
	return (bits);
}

/*
** https://en.wikipedia.org/wiki/Multiplication_algorithm
*/

static void		do_vlqmul(t_vlq const max, t_vlq const min, t_vlq *result)
{
	t_u64	part;
	t_vlq	tmp;
	t_u32	len;
	int		i;
	t_s8	j;

	len = ft_vlqlen(min);
	i = len;
	while (--i >= 0)
	{
		part = min[i];
		j = 64;
		while (--j > 0)
			if ((part << j) >> 63)
			{
				tmp = ft_vlq_bsl(max, (63 - j) + (len - 1 - i) * 63);
				ft_vlq_add_acc(result, tmp);
				ft_vlqdel(&tmp);
			}
	}
}

/*
** Basic implementation of binary multiplication with bitshift.
**
** Si t'es chaud Michel... essaye ca:
** https://en.wikipedia.org/wiki/Sch%C3%B6nhage%E2%80%93Strassen_algorithm
*/

t_vlq			ft_vlq_mul(t_vlq const a, t_vlq const b)
{
	t_vlq	result;
	t_vlq	max;
	t_vlq	min;
	long	diff;

	diff = ft_vlqcmp(a, b);
	max = diff < 0 ? b : a;
	min = diff < 0 ? a : b;
	if ((diff = ft_vlq_ispow2(max)) >= 0)
		return (ft_vlq_bsl(min, diff));
	else if ((diff = ft_vlq_ispow2(min)) >= 0)
		return (ft_vlq_bsl(max, diff));
	diff = ft_vlq_count_active_bits(a) - ft_vlq_count_active_bits(b);
	max = diff < 0 ? b : a;
	min = diff < 0 ? a : b;
	result = ft_vlqnew(1);
	do_vlqmul(max, min, &result);
	return (result);
}
