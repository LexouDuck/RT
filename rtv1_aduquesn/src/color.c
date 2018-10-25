/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

inline t_u8		color_get_a(t_u32 color)
{
	return ((t_u8)((color >> 24) & 0xFF));
}

inline t_u8		color_get_r(t_u32 color)
{
	return ((t_u8)((color >> 16) & 0xFF));
}

inline t_u8		color_get_g(t_u32 color)
{
	return ((t_u8)((color >> 8) & 0xFF));
}

inline t_u8		color_get_b(t_u32 color)
{
	return ((t_u8)(color & 0xFF));
}

inline t_u32	color_new(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_u32)((a << 24) | (r << 16) | (g << 8) | b));
}
