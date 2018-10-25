/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:14 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:16 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strpad_r(char const *str, char c, size_t length)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < length)
	{
		result[i] = str[i];
		++i;
	}
	while (i < length)
	{
		result[i] = c;
		++i;
	}
	result[length] = '\0';
	return (result);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
