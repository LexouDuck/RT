/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	char	*result;
	char	*source;
	size_t	i;

	result = (char *)dest;
	source = (char *)src;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return (dest);
}
/*
**	if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/

void	*ft_memccpy(void *dest, void const *src, int byte, size_t n)
{
	char	*result;
	char	*source;
	char	c;
	size_t	i;

	result = (char *)dest;
	source = (char *)src;
	c = (char)byte;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		if (result[i] == c)
			return (result + i + 1);
		++i;
	}
	return (NULL);
}
/*
**	if (dest == NULL || src == NULL)
**		return (NULL);
*/
