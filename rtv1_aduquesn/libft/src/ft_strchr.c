/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:12 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:13 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(char const *str, int c)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (str[i] == c)
			return ((char *)str + i);
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (NULL);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
