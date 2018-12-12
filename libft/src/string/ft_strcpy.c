/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_string.h"

char	*ft_strcpy(char *dest, char const *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}
/*
**	if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	char	*str;

	str = dest;
	while (n > 0 && *src)
	{
		*str++ = *src++;
		--n;
	}
	while (n > 0)
	{
		*str++ = '\0';
		--n;
	}
	return (dest);
}
/*
**	if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/

size_t	ft_strlcpy(char *dest, char const *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	i = 0;
	while (src[i])
		++i;
	return (i);
}
/*
**	if (dest == NULL || src == NULL)
**		return (0);
*/
