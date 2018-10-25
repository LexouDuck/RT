/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:03 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	int		start;
	int		end;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	if (!s[start])
		return (ft_strnew(0));
	end = ft_strlen(s);
	--end;
	while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
		--end;
	new = ft_strsub(s, start, end - start + 1);
	if (!new)
		return (NULL);
	return (new);
}
