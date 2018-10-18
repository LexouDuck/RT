/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:02 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:26 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strrev(const char *s)
{
	t_u32	i;
	t_u32	len;
	char	*rev;

	if (!s)
		return (NULL);
	rev = ft_strdup(s);
	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		ft_swap(&rev[i], &rev[len - 1 - i], sizeof(char));
		++i;
	}
	return (rev);
}
