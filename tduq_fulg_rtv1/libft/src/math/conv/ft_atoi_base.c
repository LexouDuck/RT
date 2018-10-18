/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:45 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:53 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

long	ft_atoi_base(const char *str, const char *base)
{
	int		i;
	long	result;
	int		neg;
	int		base_n;

	if (!str || !ft_is_valid_base(base))
		return (0);
	result = 0;
	neg = 1;
	base_n = ft_in_base('\0', base);
	i = 0;
	if (str[0] == '-')
	{
		neg = -1;
		i++;
	}
	if (str[0] == '+')
		i++;
	while (ft_in_base(str[i], base) != -1 && str[i])
		result = result * base_n + ft_in_base(str[i++], base);
	if (ft_in_base(str[i], base) == -1 && str[i] != '-' && str[i] != '+')
		return (0);
	return (result * neg);
}
