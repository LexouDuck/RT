/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:51 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((t_u8*)dest)[i] = (t_u8)((t_u8*)src)[i];
		if (((t_u8*)src)[i] == (t_u8)c)
			return ((t_u8*)dest + i + 1);
		i++;
	}
	return (NULL);
}
