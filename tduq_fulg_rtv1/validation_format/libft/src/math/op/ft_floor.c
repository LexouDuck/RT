/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:57:02 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:14:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

long		ft_floor(double lf)
{
	long	result;
	int		exp;

	exp = (((t_u64)lf << 1) >> 52) - 1023;
	if (exp > 308)
		write(2, "Double out of acceptable range in ft_floor.\n", 44);
	result = (long)lf;
	if (ft_abs(result) > 9007199254740992)
		write(2, "Untrustworthy result in ft_floor.\n", 34);
	return (result);
}
