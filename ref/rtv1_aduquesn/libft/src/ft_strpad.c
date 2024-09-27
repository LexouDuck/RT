/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:14 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:14 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strpad(char const *str, char c, size_t length)
{
	char	*result;
	int		offset;
	size_t	i;

	result = (char *)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = c;
		++i;
	}
	offset = (length - ft_strlen(str)) / 2;
	i = 0;
	while (str[i])
	{
		result[offset + i] = str[i];
		++i;
	}
	return (result);
}
