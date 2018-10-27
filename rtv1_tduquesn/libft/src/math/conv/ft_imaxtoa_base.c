/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:49 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:54 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

char	*ft_imaxtoa_base(intmax_t nb, const char *base)
{
	int		neg;
	int		size;
	int		b_n;
	int		bdigits_in_n;
	char	*arr;

	if (!base || !ft_is_valid_base(base))
		return (NULL);
	neg = nb < 0 ? 1 : 0;
	b_n = ft_in_base('\0', base);
	bdigits_in_n = ft_digits_base(nb, b_n);
	size = bdigits_in_n + neg;
	if (!(arr = ft_strnew(size)))
		return (NULL);
	if (nb == 0)
		arr[0] = base[0];
	else
		while (bdigits_in_n--)
		{
			arr[--size] = base[nb < 0 ? (b_n - (nb % b_n)) % b_n : nb % b_n];
			nb /= b_n;
		}
	if (neg)
		arr[--size] = '-';
	return (arr);
}
