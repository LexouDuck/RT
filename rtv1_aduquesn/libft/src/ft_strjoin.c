/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:13 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:15 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*result;
	size_t	length1;
	size_t	length2;
	size_t	i;

	length1 = ft_strlen(str1);
	length2 = ft_strlen(str2);
	if (!(result = (char *)malloc(length1 + length2 + 1)))
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = str1[i];
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = str2[i];
		++i;
	}
	result[length1 + length2] = '\0';
	return (result);
}
