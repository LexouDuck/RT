/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouse_objectlist_enums.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:47:32 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_bool	ui_mouse_objectlist_expandedproperties_primitive(
	t_primitive *primitive, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 0;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*primitive = (int)(*primitive == 1) ?
			PRIMITIVES - 1 : (*primitive - 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 0;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*primitive = (int)(*primitive == PRIMITIVES - 1) ?
			1 : (*primitive + 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ui_mouse_objectlist_expandedproperties_material(
	t_material *material, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 2;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*material = (int)(*material == 0) ?
			MATERIALS - 1 : (*material - 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 2;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*material = (int)(*material == MATERIALS - 1) ?
			0 : (*material + 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ui_mouse_objectlist_expandedproperties_pattern(
	t_pattern *pattern, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 4;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*pattern = (int)(*pattern == 0) ?
			TEXTURE_PATTERNS - 1 : (*pattern - 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 4;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*pattern = (int)(*pattern == TEXTURE_PATTERNS - 1) ?
			0 : (*pattern + 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ui_mouse_objectlist_expandedproperties_projection(
	t_projection *projection, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 6;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*projection = (int)(*projection == 0) ?
			TEXTURE_PROJECTIONS - 1 : (*projection - 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 6;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*projection = (int)(*projection == TEXTURE_PROJECTIONS - 1) ?
			0 : (*projection + 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ui_mouse_objectlist_expandedproperties_bump(
	t_bump *bump_type, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 8;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*bump_type = (int)(*bump_type == 0) ?
			BUMP_TYPES - 1 : (*bump_type - 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 8;
	if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
	{
		*bump_type = (int)(*bump_type == BUMP_TYPES - 1) ?
			0 : (*bump_type + 1);
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}
