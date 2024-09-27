/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:32:17 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:21 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char			*ft_strcdup(char const *str, char const c)
{
	char		*result;
	size_t		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		++i;
	}
	result = ft_strsub(str, 0, i);
	return (result);
}
