/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:13 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:14 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(char const *str)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(ft_strlen(str) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
