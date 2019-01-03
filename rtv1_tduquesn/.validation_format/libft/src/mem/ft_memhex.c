/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:25:31 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:48 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_str.h"

char	*ft_memhex(const void *s, size_t n)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*hex_base;

	if (!s)
		return (NULL);
	hex_base = HXUPP;
	if (!(new_str = ft_strnew(n * 2)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		new_str[j++] = hex_base[((t_u8*)s)[i] / 16];
		new_str[j++] = hex_base[((t_u8*)s)[i] % 16];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
