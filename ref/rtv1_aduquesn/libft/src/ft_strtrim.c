/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:18 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *str)
{
	size_t	offset;
	size_t	length;

	offset = 0;
	length = ft_strlen(str);
	while (offset < length && (
		str[offset] == ' ' ||
		str[offset] == '\n' ||
		str[offset] == '\t'))
	{
		++offset;
	}
	if (offset == length)
		return (ft_strsub(str, 0, 0));
	length -= 1;
	while (length > offset && (
		str[length] == ' ' ||
		str[length] == '\n' ||
		str[length] == '\t'))
	{
		--length;
	}
	length -= offset - 1;
	return (ft_strsub(str, offset, length));
}
/*
**	if (str == NULL)
**		return (NULL);
*/
