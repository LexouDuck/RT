/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipowi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_u64	ft_ipowi(t_u32 nb, t_u8 power)
{
	t_u32		tmp;

	if (power == 0)
		return (1);
	tmp = ft_ipowi(nb, power / 2);
	if (power % 2 == 0)
		return (tmp * tmp);
	else
		return (nb * tmp * tmp);
}
