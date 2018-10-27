/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:49 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:56 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

char	*ft_uitoa_base(unsigned long nb, const char *base)
{
	int		size;
	int		b_n;
	int		bdigits_in_n;
	char	*arr;

	if (!base || !ft_is_valid_base(base))
		return (NULL);
	b_n = ft_in_base('\0', base);
	bdigits_in_n = ft_udigits_base(nb, b_n);
	size = bdigits_in_n;
	if (!(arr = ft_strnew(size)))
		return (NULL);
	if (nb == 0)
		arr[0] = base[0];
	else
		while (bdigits_in_n--)
		{
			arr[--size] = base[nb % b_n];
			nb /= b_n;
		}
	return (arr);
}
