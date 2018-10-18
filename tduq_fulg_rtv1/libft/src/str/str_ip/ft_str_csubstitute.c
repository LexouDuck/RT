/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_csubstitute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 01:24:59 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

/*
** Works like the bash function tr. Substitute tr_f[i] by tr_t[i] in str.
** Fails silently if input is null, if strlen is different for tr_f and tr_t,
** or if a character is repeated in tr_f (only one image for every antecedent).
*/

void		ft_str_csubstitute(char *str, char const *tr_f, char const *tr_t)
{
	t_u32	i;
	t_u32	j;
	int		c_i;

	if (!tr_f || !tr_t || ft_strlen(tr_f) != ft_strlen(tr_t))
		return ;
	i = 0;
	while (tr_f[i])
	{
		j = i;
		while (tr_f[++j])
			if (tr_f[i] == tr_f[j])
				return ;
		++i;
	}
	i = 0;
	while (str[i])
	{
		if ((c_i = ft_strfind(tr_f, str[i])) >= 0)
			str[i] = tr_t[c_i];
		++i;
	}
}
