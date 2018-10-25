/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:39:25 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned long	ft_getbits(void *ptr, int bit, int length)
{
	int mask;
	int i;

	if (ptr == NULL)
		return (0);
	mask = 0;
	i = 0;
	while (i < length)
	{
		mask <<= 1;
		mask |= 1;
		++i;
	}
	return ((*((t_u64 *)ptr) >> bit) & mask);
}
