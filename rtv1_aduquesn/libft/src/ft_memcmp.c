/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:10 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 00:10:52 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(void const *ptr1, void const *ptr2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((t_u8 *)ptr1)[i] != ((t_u8 *)ptr2)[i])
			return (((t_u8 *)ptr1)[i] - ((t_u8 *)ptr2)[i]);
		++i;
	}
	return (0);
}
/*
**	if (ptr1 == ptr2)
**		return (0);
**	return (ptr1 == NULL ? 0 : ptr1[0]) -
**		   (ptr2 == NULL ? 0 : ptr2[0]);
*/
