/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_sub_acc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 06:51:10 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Does acc = acc - vlq with a minimum of 0 return value in acc. Fails with
** output to stderr when given improper parameters and returns 0 in acc if
** vlq > acc.
*/

void					ft_vlq_sub_acc(t_vlq *acc, t_vlq const vlq)
{
	t_vlq	result;

	if (!acc || !*acc || !vlq || (ft_msb(**acc) && !ft_not_msb(**acc)))
	{
		ft_putendl_fd("Invalid accumulator in vlq_sub_acc.", 2);
		return ;
	}
	if (ft_vlqcmp(*acc, vlq) < 0)
	{
		ft_vlqdel(acc);
		*acc = 0;
		return ;
	}
	result = ft_vlq_sub(*acc, vlq);
	ft_vlqdel(acc);
	*acc = result;
}
