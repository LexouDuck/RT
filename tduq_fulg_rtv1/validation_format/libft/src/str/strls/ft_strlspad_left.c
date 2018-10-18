/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlspad_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:28:46 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:48 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	**ft_strlspad_left(const char **strls, const char c, t_u32 n)
{
	char		**result;
	t_u32		pt_a_len;
	t_u32		i;

	if (!strls)
		return (NULL);
	pt_a_len = ft_ptrarrlen(strls);
	if (!(result = (char**)malloc(sizeof(char*) * (pt_a_len + 1))))
		return (NULL);
	i = 0;
	while (strls[i])
	{
		result[i] = ft_strpad_left(strls[i], c, n);
		if (!result[i])
		{
			ft_strlsdel(&result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
