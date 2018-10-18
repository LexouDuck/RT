/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:05:07 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Note that bitshift right on a negative long is implementation defined (can
** fill memory with zeros or ones, so we made a version of carry here that works
** with both).
*/

static t_vlq	do_vlqsub(t_vlq const max, t_vlq const min)
{
	t_vlq	result;
	int		max_len;
	int		min_len;
	long	cur_part;
	t_u64	carry;

	max_len = ft_vlqlen(max) - 1;
	min_len = ft_vlqlen(min) - 1;
	result = ft_vlqnew(max_len + 1);
	carry = 0;
	while (max_len >= 0)
	{
		cur_part = ft_not_msb(max[max_len]);
		cur_part -= (min_len >= 0) ? ft_not_msb(min[min_len]) : 0;
		cur_part -= carry ? 1 : 0;
		carry = ft_msb(cur_part);
		result[max_len] |= ft_not_msb(cur_part);
		--max_len;
		--min_len;
	}
	ft_vlqtrim(&result);
	return (result);
}

/*
** Subtraction operator. Always returns ABS(a-b).
*/

t_vlq			ft_vlq_sub(t_vlq const a, t_vlq const b)
{
	t_vlq	result;
	t_vlq	max;
	t_vlq	min;
	long	diff;

	diff = ft_vlqcmp(a, b);
	min = diff < 0 ? a : b;
	max = diff < 0 ? b : a;
	result = do_vlqsub(max, min);
	return (result);
}
