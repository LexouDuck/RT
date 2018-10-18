/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_in_interval.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 09:06:21 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/04 09:06:25 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

inline t_bool		ft_float_in_interval(t_float x, t_float start, t_float end)
{
	return (start <= x && x <= end);
}
