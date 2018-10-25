/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:49 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

int		ft_is_valid_base(const char *base)
{
	int		i;
	int		j;
	int		size;
	char	c;

	if (!base)
		return (0);
	size = ft_in_base('\0', base);
	i = 0;
	while (i < size - 1)
	{
		c = base[i];
		if (c == '+' || c == '-' || !ft_isprint(base[i]))
			return (0);
		j = i;
		while (base[++j])
			if (base[j] == c)
				return (0);
		i++;
	}
	if (base[i] == '+' || base[i] == '-' || !ft_isprint(base[i]))
		return (0);
	return (1);
}
