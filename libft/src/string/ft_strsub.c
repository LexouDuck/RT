/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_string.h"

char	*ft_strsub(char const *str, size_t offset, size_t n)
{
	char	*result;
	size_t	length;
	size_t	i;

	length = 0;
	while (str[length])
		++length;
	if (offset > length || offset + n > length)
		return (NULL);
	if (!(result = (char *)malloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
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
