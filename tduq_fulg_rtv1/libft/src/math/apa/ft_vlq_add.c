/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 06:07:41 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:31 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Maybe improve size management to avoid call to vlqtrim : there is a carry iff
** the union of the two operands has a series of leading 1s, and at its inter-
** section has at least 1 bit in common with that series.
** Use inspiration from here for bwa and bwo
*/

t_vlq		ft_vlq_add(t_vlq const a, t_vlq const b)
{
	t_vlq	result;
	int		a_len;
	int		b_len;
	t_u64	cur_part;
	t_u64	carry;

	a_len = ft_vlqlen(a) - 1;
	b_len = ft_vlqlen(b) - 1;
	result = ft_vlqnew((ft_max(a_len, b_len) + 2));
	carry = 0;
	while (a_len >= 0 || b_len >= 0 || carry)
	{
		cur_part = carry;
		cur_part += (a_len >= 0) ? ft_not_msb(a[a_len]) : 0;
		cur_part += (b_len >= 0) ? ft_not_msb(b[b_len]) : 0;
		carry = ft_msb(cur_part);
		result[ft_max(a_len, b_len) + 1] |= ft_not_msb(cur_part);
		--a_len;
		--b_len;
	}
	ft_vlqtrim(&result);
	return (result);
}
