/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_insert_inplace.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:23:03 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void		ft_strpad_insert_inplace(char **a_str, char const c,
										t_u32 start, size_t len)
{
	char	*tmp;

	tmp = ft_strcnew(len, c);
	ft_strinsert(a_str, tmp, start);
	ft_strdel(&tmp);
}
