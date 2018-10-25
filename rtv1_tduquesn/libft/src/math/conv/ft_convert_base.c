/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:46 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:54 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

char	*ft_convert_base(const char *n, const char *base_f, const char *base_t)
{
	int		i;
	long	nb;
	int		symbols_bf;
	int		symbols_bt;
	char	*new_n;

	if (!n || !base_f || !base_t)
		return (NULL);
	symbols_bf = ft_in_base('\0', base_f);
	symbols_bt = ft_in_base('\0', base_t);
	if (!ft_is_valid_base(base_f) || !ft_is_valid_base(base_t) ||
		!n || !n[0] || symbols_bf <= 1 || symbols_bt <= 1)
		return (NULL);
	i = -1;
	while (n[++i])
		if (ft_in_base(n[i], base_f) == -1 && n[i] != '+' && n[i] != '-')
			return (NULL);
	nb = (long)ft_atoi_base(n, base_f);
	new_n = ft_itoa_base(nb, base_t);
	return (new_n);
}
