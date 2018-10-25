/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:12 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:13 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	size_t	length;
	size_t	i;

	length = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[length + i] = src[i];
		++i;
	}
	dest[length + i] = '\0';
	return (dest);
}
/*
**	if (dest == NULL)
**		return (NULL);
**	if (src == NULL)
**		return (dest);
*/
