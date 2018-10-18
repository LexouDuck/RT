/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim_right_inplace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:16:15 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void	ft_strctrim_right_inplace(char **a_str, char const c)
{
	int		i;

	if (!a_str || !(*a_str))
		return ;
	i = ft_strlen(*a_str) - 1;
	while ((*a_str)[i] == c)
	{
		(*a_str)[i] = '\0';
		--i;
	}
}
