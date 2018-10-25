/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:01:26 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:16:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strmerge(char **a_s1, char **a_s2)
{
	char	*result;

	result = ft_strjoin(*a_s1, *a_s2);
	ft_strdel(a_s1);
	ft_strdel(a_s2);
	*a_s1 = result;
	*a_s2 = result;
	return (result);
}
