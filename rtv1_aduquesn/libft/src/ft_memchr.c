/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:10 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:11 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(void const *ptr, int byte, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((t_u8 *)ptr)[i] == (t_u8)byte)
			return ((t_u8 *)ptr + i);
		++i;
	}
	return (NULL);
}
/*
**	if (ptr == NULL)
**		return (NULL);
*/
