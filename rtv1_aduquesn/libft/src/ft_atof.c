/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:44:38 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

float	ft_atof(const char *str)
{
	float	result;
	float	factor;
	int		point_seen;

	result = 0;
	factor = 1;
	if (*str == '-')
	{
		str++;
		factor = -1;
	}
	point_seen = 0;
	while (*str)
	{
		if (*str == '.')
			point_seen = 1;
		else if (ft_isdigit(*str))
		{
			if (point_seen)
				factor /= 10.0f;
			result = result * 10.0f + (float)(*str - '0');
		}
		++str;
	}
	return (result * factor);
}
