/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntrim_right_inplace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:21:37 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void		ft_strntrim_right_inplace(char **a_str, size_t n)
{
	int		len;

	if (!a_str || !(*a_str))
		return ;
	len = ft_strlen(*a_str) - n;
	if (len < 0)
		len = 0;
	(*a_str)[len] = '\0';
}
