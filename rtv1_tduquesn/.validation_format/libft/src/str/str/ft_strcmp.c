/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:58 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:21 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		s1_len;
	int		s2_len;
	int		min;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	min = s1_len < s2_len ? s1_len : s2_len;
	return (ft_memcmp(s1, s2, min + 1));
}
