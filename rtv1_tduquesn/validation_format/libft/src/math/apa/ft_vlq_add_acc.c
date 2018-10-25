/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_add_acc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 06:51:10 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:30 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

void					ft_vlq_add_acc(t_vlq *acc, t_vlq const vlq)
{
	t_vlq	result;

	result = ft_vlq_add(*acc, vlq);
	ft_vlqdel(acc);
	*acc = result;
}
