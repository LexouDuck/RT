/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlscnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 04:41:59 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	**ft_strlscnew(t_u32 y, size_t x, const char c)
{
	char	**strls;
	t_u32	i;

	if (!(strls = (char**)ft_ptrarrnew(y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(strls[i] = ft_strnew(x)))
		{
			strls[i] = NULL;
			ft_strlsdel(&strls);
			return (NULL);
		}
		ft_memset(strls[i], c, x);
		strls[i++][x] = '\0';
	}
	strls[y] = NULL;
	return (strls);
}
