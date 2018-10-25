/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:53 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:48 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	t_u8	tmp[4096];
	t_u32	i;

	i = 0;
	while ((i + 1) * 4096 < n)
	{
		ft_memcpy(tmp, (t_u8*)src + i * 4096, 4096);
		ft_memcpy((t_u8*)dest + i * 4096, tmp, 4096);
		i++;
	}
	n %= 4096;
	ft_memcpy(tmp, (t_u8*)src + i * 4096, n);
	ft_memcpy((t_u8*)dest + i * 4096, tmp, n);
	return (dest);
}
