/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_memory.h"

void	*ft_memdup(const void *ptr, size_t n)
{
	char	*result;
	char	*source;
	size_t	i;

	if (ptr == NULL)
		return (NULL);
	if (!(result = (char *)malloc(n)))
		return (NULL);
	source = (char *)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return ((void *)result);
}
