/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 02:39:20 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsub(char const *str, size_t offset, size_t length)
{
	char	*result;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(str);
	if (offset > str_len || length > str_len)
		return (NULL);
	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[offset + i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
