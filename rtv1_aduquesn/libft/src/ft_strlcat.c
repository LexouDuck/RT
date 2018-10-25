/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:13 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/21 20:14:12 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dest);
	if (dst_len >= size)
		dst_len = size;
	if (dst_len != size)
	{
		i = 0;
		while (dst_len + i + 1 < size && src[i])
		{
			dest[dst_len + i] = src[i];
			++i;
		}
		dest[dst_len + i] = '\0';
	}
	return (dst_len + src_len);
}
/*
**	if (dest == NULL)
**		return (0);
**
**	if (src == NULL)
**		return (length);
*/
