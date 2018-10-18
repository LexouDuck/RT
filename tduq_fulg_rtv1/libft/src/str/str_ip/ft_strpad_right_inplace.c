/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_right_inplace.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 19:23:07 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:38 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void	ft_strpad_right_inplace(char **a_str, char const c, t_u32 len)
{
	char	*tmp;

	if (len == 0)
		return ;
	tmp = ft_strpad_right(*a_str, c, len);
	ft_strdel(a_str);
	*a_str = tmp;
}
