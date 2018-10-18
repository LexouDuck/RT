/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:59 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:23 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*sum;
	t_u32		len1;
	t_u32		len2;

	if (!s1 && !s2)
		return (ft_strnew(0));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(sum = (char*)malloc(len1 + len2 + 1)))
		return (NULL);
	ft_strcpy(sum, s1);
	ft_strcat(sum, s2);
	sum[len1 + len2] = '\0';
	return (sum);
}
