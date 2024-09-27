/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:14 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:16 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(char const *str, char const *query, size_t n)
{
	size_t	length;
	size_t	match;
	size_t	i;

	length = ft_strlen(query);
	i = 0;
	while (str[i] && i + length <= n)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				match++;
			else
				break ;
		}
		if (match == length)
			return ((char *)str + i);
		++i;
	}
	return (NULL);
}
/*
**	if (str == NULL || query == NULL)
**		return (NULL);
*/
