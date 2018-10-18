/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:51 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_memalloc(size_t size)
{
	t_u8		*p;

	p = NULL;
	if (!(p = (t_u8*)malloc(size)))
		return (NULL);
	ft_bzero(p, size);
	return (p);
}
