/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 00:44:37 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:23 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strhex(const char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*hex_base;

	if (!str)
		return (NULL);
	hex_base = HXUPP;
	if (!(new_str = ft_strnew(ft_strlen(str) * 2)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		new_str[j++] = hex_base[((t_u8)str[i]) / 16];
		new_str[j++] = hex_base[((t_u8)str[i]) % 16];
		++i;
	}
	new_str[j] = '\0';
	return (new_str);
}
