/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_pow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:13:12 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Uses exponentiation by squares to return a ^ exp.
*/

t_vlq		ft_vlq_pow(t_vlq const a, t_vlq const exp)
{
	t_vlq	result;
	t_vlq	tmp_a;
	t_u32	sigbits;
	t_u32	len;
	t_s8	cur_sigpos;

	if (!a || !exp)
		return (NULL);
	result = ft_atovlq("1", BINAR);
	tmp_a = ft_vlqdup(a);
	len = ft_vlqlen(exp) - 1;
	sigbits = ft_vlq_count_sigbit(exp) + 1;
	cur_sigpos = 63;
	while (--sigbits)
	{
		if ((exp[len] << (cur_sigpos)) >> 63)
			ft_vlq_mul_acc(&result, tmp_a);
		cur_sigpos = cur_sigpos == 1 ? 63 : cur_sigpos - 1;
		if (cur_sigpos == 63)
			--len;
		ft_vlq_mul_acc(&tmp_a, tmp_a);
	}
	ft_vlqdel(&tmp_a);
	return (result);
}
