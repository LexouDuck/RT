/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_count_sigbit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 02:56:22 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Returns the number of significant bits in our whole vlq, or 0 if the vlq
** is improperly formatted. The number 0 has 1 significant bit.
*/

t_u32			ft_vlq_count_sigbit(t_vlq vlq)
{
	t_u32	full_indices;

	if (*vlq == 0)
		return (1);
	if (!ft_not_msb(vlq[0]))
		return (0);
	full_indices = ft_vlqlen(vlq) - 1;
	return (ft_vlq_count_sigbit_of_part(vlq[0]) + 63 * full_indices);
}
