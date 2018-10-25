/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlssub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 02:11:23 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:48 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	**ft_strlssub(const char **strls, t_u32 start, t_u32 len)
{
	t_u32		i;
	char		**result;

	if (!strls || start + len >= ft_ptrarrlen(strls))
		return (NULL);
	if (!(result = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!(result[i] = ft_strdup(strls[i + start])))
		{
			ft_strlsdel(&result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
