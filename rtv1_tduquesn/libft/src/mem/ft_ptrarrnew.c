/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarrnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:22 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:49 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_ptrarrnew(t_u32 len)
{
	void	*result;

	if (!(result = ft_memalloc(sizeof(void*) * (len + 1))))
		return (NULL);
	return (result);
}
