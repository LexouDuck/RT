/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_containsonly.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 18:43:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/21 18:58:05 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

int		ft_str_containsonly(char const *str, char const *chars)
{
	int		i;

	i = -1;
	while (str[++i])
		if (ft_strfind(chars, str[i]) == -1)
			return (0);
	return (1);
}
