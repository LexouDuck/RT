/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/21 21:55:26 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strsplit_get_count(char const *str, char c)
{
	int		result;
	int		separator;
	size_t	i;

	separator = 1;
	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			separator = 1;
			++i;
		}
		if (str[i])
		{
			if (separator)
				++result;
		}
		else
			break ;
		separator = 0;
		++i;
	}
	return (result);
}

char		**ft_strsplit(char const *str, char c)
{
	char	**result;
	size_t	offset;
	size_t	length;
	int		count;
	int		i;

	count = ft_strsplit_get_count(str, c);
	if (!(result = (char **)malloc((count + 1) * sizeof(char *))))
		return (NULL);
	offset = 0;
	length = 0;
	i = 0;
	while (i < count)
	{
		offset += length;
		while (str[offset] && str[offset] == c)
			++offset;
		length = 0;
		while (str[offset + length] && str[offset + length] != c)
			++length;
		if (length > 0)
			result[i++] = ft_strsub(str, offset, length);
	}
	result[count] = NULL;
	return (result);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
