/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:52 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
	{
		write(2, "null operand given to ft_memcpy.\n", 33);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		((t_u8*)dest)[i] = ((t_u8*)src)[i];
		i++;
	}
	return (dest);
}
