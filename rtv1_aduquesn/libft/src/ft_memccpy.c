/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:10 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:11 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *dest, void const *src, int byte, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((t_u8 *)dest)[i] = ((t_u8 *)src)[i];
		if (((t_u8 *)dest)[i++] == (t_u8)byte)
			return (dest + i);
	}
	return (NULL);
}
/*
**	if (dest == NULL || src == NULL)
**		return (NULL);
*/
