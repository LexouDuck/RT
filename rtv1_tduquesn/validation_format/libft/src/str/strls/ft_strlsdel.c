/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 00:46:24 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void	ft_strlsdel(char ***a_strls)
{
	int		i;

	if (a_strls && *a_strls)
	{
		i = 0;
		while ((*a_strls)[i])
		{
			ft_strdel((*a_strls) + i);
			++i;
		}
		ft_memdel((void**)a_strls);
	}
}
