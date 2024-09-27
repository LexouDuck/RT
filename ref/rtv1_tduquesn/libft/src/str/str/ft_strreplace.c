/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 02:55:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:26 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strreplace(char const *str, char const *sub, char const *rep)
{
	char	**strls;
	char	*result;

	strls = ft_strsplitstr(str, sub);
	result = ft_strlsjoin((const char **)strls, rep);
	ft_strlsdel(&strls);
	return (result);
}
