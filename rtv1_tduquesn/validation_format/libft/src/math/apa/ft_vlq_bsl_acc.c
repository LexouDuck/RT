/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_bsl_acc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:41:55 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:31 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

void		ft_vlq_bsl_acc(t_vlq *a_vlq, t_u32 shift)
{
	t_vlq	tmp;

	tmp = ft_vlq_bsl(*a_vlq, shift);
	ft_vlqdel(a_vlq);
	*a_vlq = tmp;
}
