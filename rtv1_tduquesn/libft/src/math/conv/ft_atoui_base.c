/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:45 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:13:54 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_u64		ft_atoui_base(const char *str, const char *base)
{
	int		i;
	t_u64	result;
	int		base_n;

	if (!str || !ft_is_valid_base(base))
		return (0);
	result = 0;
	base_n = ft_in_base('\0', base);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (ft_in_base(str[i], base) != -1 && str[i])
		result = result * base_n + ft_in_base(str[i++], base);
	if (ft_in_base(str[i], base) == -1)
		return (0);
	return (result);
}
