/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

t_u64	ft_getbits(t_u64 value, int bit, int length)
{
	t_u64	mask;
	int		i;

	mask = 0;
	i = 0;
	while (i < length)
	{
		mask <<= 1;
		mask |= 1;
		++i;
	}
	return ((value >> bit) & mask);
}
