/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:51:11 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

t_vlq		ft_vlqnew(t_u32 size)
{
	t_vlq	result;
	t_u32	i;

	if (size == 0)
		return (NULL);
	if (!(result = malloc(sizeof(t_u64) * size)))
		return (NULL);
	size = size - 1;
	i = 0;
	while (i < size)
	{
		result[i] = _MSB_;
		++i;
	}
	result[i] = 0;
	return (result);
}
