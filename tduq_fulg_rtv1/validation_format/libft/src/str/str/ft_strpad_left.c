/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 04:24:22 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:25 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strpad_left(const char *s, char const c, t_u32 n)
{
	t_u32	i;
	t_u32	len;
	char	*result;

	if (!s)
		return (NULL);
	len = n + ft_strlen(s);
	if (!(result = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = c;
		++i;
	}
	ft_strlcpy(result + i, s, ft_strlen(s) + 1);
	return (result);
}
