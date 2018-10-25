/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:11 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:12 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	size_t	i;

	if (dest == src)
		return (dest);
	if (src < dest && src + n >= dest)
	{
		i = n;
		while (i--)
			((t_u8 *)dest)[i] = ((t_u8 *)src)[i];
	}
	else
	{
		i = -1;
		while (++i < n)
			((t_u8 *)dest)[i] = ((t_u8 *)src)[i];
	}
	return (dest);
}
/*
** if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/
