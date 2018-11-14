/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	char	*result;
	char	*source;
	size_t	i;

	if (dest == src)
		return (dest);
	result = (char *)dest;
	source = (char *)src;
	if (src < dest && src + n >= dest)
	{
		i = n;
		while (i--)
			result[i] = source[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			result[i] = source[i];
			++i;
		}
	}
	return (dest);
}
/*
** if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/
