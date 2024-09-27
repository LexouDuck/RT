/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:14 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/18 18:08:25 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	char *str;

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
