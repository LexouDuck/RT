/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:36:34 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char			*ft_strappend(char **dest, char const *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dest, src);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}
