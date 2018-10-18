/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:01 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:25 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	return (ft_strncmp(s1, s2, n) == 0);
}
