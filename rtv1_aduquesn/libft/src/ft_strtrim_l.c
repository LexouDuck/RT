/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:15 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	strtrim_charset_contains(char const *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char		*ft_strtrim_l(char const *str, char const *charset)
{
	size_t	i;
	size_t	length;

	length = ft_strlen(str);
	i = 0;
	while (i < length)
	{
		if (strtrim_charset_contains(charset, str[i]))
			++i;
		else
			break ;
	}
	length -= i;
	return (ft_strsub(str, i, length));
}
/*
**	if (str == NULL || charset == NULL)
**		return (NULL);
*/
