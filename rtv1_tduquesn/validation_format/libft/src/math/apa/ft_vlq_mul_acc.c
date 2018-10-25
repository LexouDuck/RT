/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_mul_acc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:55:00 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

void		ft_vlq_mul_acc(t_vlq *acc, t_vlq const vlq)
{
	t_vlq	tmp;

	tmp = ft_vlq_mul(*acc, vlq);
	ft_vlqdel(acc);
	*acc = tmp;
}
