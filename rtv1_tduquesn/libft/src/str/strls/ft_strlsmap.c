/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 21:32:00 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char		**ft_strlsmap(char const **strls, char *(*f)(char const *))
{
	t_u32	i;
	char	**result;

	if (!strls || !*strls || !f ||
		!(result = ft_ptrarrnew(ft_ptrarrlen(strls))))
		return (NULL);
	i = 0;
	while (strls[i])
	{
		result[i] = (*f)(strls[i]);
		++i;
	}
	return (result);
}
