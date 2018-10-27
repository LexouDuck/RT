/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:36:24 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

static t_u32	count_unprintables(char const *str)
{
	t_u32	i;
	t_u32	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			++count;
		++i;
	}
	return (count);
}

static char		get_hex(t_u8 const c, t_u8 const pow)
{
	char	*base;

	base = HXLOW;
	if (pow)
		return (base[c / 16]);
	else
		return (base[c % 16]);
}

char			*ft_str_toprint(char const *str)
{
	char	*result;
	t_u32	uprint;
	t_u32	i;
	t_u32	cur_uprint;

	uprint = count_unprintables(str);
	if (!(result = ft_strnew(ft_strlen(str) + uprint * 3)))
		return (NULL);
	cur_uprint = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			result[i + 3 * cur_uprint] = str[i];
		else
		{
			result[i + 3 * cur_uprint] = '\\';
			result[i + 3 * cur_uprint + 1] = 'x';
			result[i + 3 * cur_uprint + 2] = get_hex(str[i], 1);
			result[i + 3 * cur_uprint + 3] = get_hex(str[i], 0);
			++cur_uprint;
		}
		++i;
	}
	return (result);
}
