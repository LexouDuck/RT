/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfpowi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

double		ft_lfpowi(double lf, int power)
{
	double		tmp;

	if (power == 0)
		return (1.);
	tmp = ft_lfpowi(lf, power / 2);
	if (power % 2 == 0)
		return (tmp * tmp);
	else
	{
		if (power > 0)
			return (lf * tmp * tmp);
		else
			return (tmp * tmp / lf);
	}
}
