/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:53 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_memdup(const void *s, size_t n)
{
	void	*dup;

	if (!(dup = malloc(n)))
		return (NULL);
	dup = ft_memcpy(dup, s, n);
	return (dup);
}
