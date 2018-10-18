/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:04:14 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strinsert(char **dest, char const *src, t_u32 index)
{
	char	*tmp;

	tmp = ft_strsub(*dest, 0, index);
	ft_strappend(&tmp, src);
	ft_strappend(&tmp, (*dest) + index);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}
