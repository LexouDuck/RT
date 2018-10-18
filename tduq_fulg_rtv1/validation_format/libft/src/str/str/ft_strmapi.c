/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:00 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:24 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	t_u32	i;
	char	*new;

	if (!s || !f || !(new = (char*)malloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = (*f)(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
