/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev_inplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 05:57:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:38 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void			ft_strrev_inplace(char **a_str)
{
	t_u32	i;
	t_u32	len;

	if (!a_str || !*a_str)
		return ;
	len = ft_strlen(*a_str);
	i = 0;
	while (i < len / 2)
	{
		ft_swap(*a_str + i, *a_str + len - 1 - i, sizeof(char));
		++i;
	}
}
