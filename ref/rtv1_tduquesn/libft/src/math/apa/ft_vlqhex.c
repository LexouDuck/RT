/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 16:45:49 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** Returns a string of all the u64 in a vlq, as they are (with MSB) in 0xHXLOW.
*/

char	*ft_vlqhex(t_vlq const vlq)
{
	char		*result;
	char		*tmp;
	t_u32		i;
	t_u32		len;
	t_u32		columns;

	if (!vlq)
		return (ft_strdup("(null_vlq)"));
	columns = 8;
	result = ft_strdup("0x");
	len = ft_vlqlen(vlq);
	i = 0;
	while (i < len)
	{
		tmp = ft_uitoa_base(vlq[i], HXLOW);
		ft_strpad_left_inplace(&tmp, '0', 16 - ft_strlen(tmp));
		ft_strappend(&tmp, (i + 1) % columns ? ", 0x" : ",\n 0x");
		ft_strappend(&result, tmp);
		ft_strdel(&tmp);
		++i;
	}
	ft_strntrim_right_inplace(&result, 4 + (i % columns == 0));
	return (result);
}
