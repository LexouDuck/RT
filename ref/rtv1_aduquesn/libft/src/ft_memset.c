/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:11 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:12 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *ptr, int byte, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((t_u8 *)ptr)[i] = byte;
		++i;
	}
	return (ptr);
}
/*
**	if (ptr == NULL)
**		return (NULL);
*/
