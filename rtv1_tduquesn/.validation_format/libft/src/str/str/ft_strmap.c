/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:00 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:24 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	t_u32	i;
	char	*new;

	if (!s || !f || !(new = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = (*f)(s[i]);
		++i;
	}
	return (new);
}
