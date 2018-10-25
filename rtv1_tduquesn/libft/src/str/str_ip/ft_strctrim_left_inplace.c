/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim_left_inplace.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:00:47 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void		ft_strctrim_left_inplace(char **a_str, char const c)
{
	int		i;
	char	*tmp;

	if (!a_str || !(*a_str))
		return ;
	if ((*a_str)[0] != c)
		return ;
	i = 0;
	while ((*a_str)[i] == c)
		++i;
	tmp = (*a_str)[i] ? ft_strdup((*a_str) + i) : ft_strnew(0);
	ft_strdel(a_str);
	*a_str = tmp;
}
