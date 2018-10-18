/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:52 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	t_u8		*sc1;
	t_u8		*sc2;

	sc1 = (t_u8*)s1;
	sc2 = (t_u8*)s2;
	i = 0;
	while (i < n)
	{
		if (sc1[i] != sc2[i])
			return ((int)sc1[i] - (int)sc2[i]);
		i++;
	}
	return (0);
}
