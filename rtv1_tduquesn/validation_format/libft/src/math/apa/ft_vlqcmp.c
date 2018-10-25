/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 06:18:38 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:31 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

long	ft_vlqcmp(t_vlq const a, t_vlq const b)
{
	long	diff;
	t_u32	a_len;
	t_u32	i;

	if ((!ft_not_msb(a[0]) && ft_msb(a[0]))
		|| (!ft_not_msb(b[0]) && ft_msb(b[0])))
	{
		ft_putendl_fd("Improper vlq in vlqcmp.", 2);
		return (0);
	}
	a_len = ft_vlqlen(a);
	diff = a_len - ft_vlqlen(b);
	if (diff == 0)
	{
		i = 0;
		while (i < a_len && a[i] == b[i])
			++i;
		return (i == a_len ? 0 : ft_not_msb(a[i]) - ft_not_msb(b[i]));
	}
	else
		return (diff);
}
