/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsmap_inplace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 21:32:00 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void		ft_strlsmap_inplace(char ***a_strls, char *(*f)(char *))
{
	t_u32	i;
	char	*tmp;

	if (!a_strls || !*a_strls || !f)
		return ;
	i = 0;
	while (a_strls[i])
	{
		tmp = (*f)((*a_strls)[i]);
		if (tmp != (*a_strls)[i])
			ft_strdel(*a_strls + i);
		(*a_strls)[i] = tmp;
		++i;
	}
}
