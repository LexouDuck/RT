/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:02 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:25 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char*)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j])
		{
			if (little[j + 1] == '\0')
				return ((char*)big + i);
			if (i + j >= len)
				return (NULL);
			++j;
		}
		++i;
	}
	return (NULL);
}
