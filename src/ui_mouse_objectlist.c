/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:47:32 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

#include "../rt.h"
#include "debug.h"

static t_bool	ui_mouse_objectlist_expandedproperties_primitive(
	t_primitive *primitive, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 0;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*primitive = (int)(*primitive == 1) ? PRIMITIVES - 1 : (*primitive - 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 0;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*primitive = (int)(*primitive == PRIMITIVES - 1) ? 1 : (*primitive + 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ui_mouse_objectlist_expandedproperties_material(
	t_material *material, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 2;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*material = (int)(*material == 0) ? MATERIALS - 1 : (*material - 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 2;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*material = (int)(*material == MATERIALS - 1) ? 0 : (*material + 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ui_mouse_objectlist_expandedproperties_pattern(
	t_pattern *pattern, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 4;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*pattern = (int)(*pattern == 0) ? TEXTURE_PATTERNS - 1 : (*pattern - 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 4;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*pattern = (int)(*pattern == TEXTURE_PATTERNS - 1) ? 0 : (*pattern + 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ui_mouse_objectlist_expandedproperties_projection(
	t_uv_projection *projection, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.x = 12;
	rect.y = y + 6;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*projection = (int)(*projection == 0) ? TEXTURE_PROJECTIONS - 1 : (*projection - 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 24;
	rect.y = y + 6;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*projection = (int)(*projection == TEXTURE_PROJECTIONS - 1) ? 0 : (*projection + 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static void	ui_mouse_objectlist_expandedproperties(t_object *object, t_s32 y)
{
	cl_float3		*ptr;
	t_u8			i;

	if (ui_mouse_objectlist_expandedproperties_primitive(&object->type, y) ||
		ui_mouse_objectlist_expandedproperties_material(&object->material, y) ||
		ui_mouse_objectlist_expandedproperties_pattern(&object->pattern, y) ||
		ui_mouse_objectlist_expandedproperties_projection(&object->uv_projection, y))
		return ;
	y += 8;
	ptr = &object->rgb_a;
	i = 0;
	while (i < OBJECT_PROPERTIES)
	{
		ui_mouse_control_numberbox(&rt.ui.current_textinput, &ptr->x, 1, y + 1);
		ui_mouse_control_numberbox(&rt.ui.current_textinput, &ptr->y, 10, y + 1);
		ui_mouse_control_numberbox(&rt.ui.current_textinput, &ptr->z, 19, y + 1);
		y += OBJECT_PROPERTY_H;
		++ptr;
		++i;
	}
	update_object(object);
}

void		ui_mouse_objectlist(void)
{
	t_s32		tmp;
	t_s32		add_height;
	SDL_Rect	rect;
	t_u32		i;

	rect = rt.ui.objects.rect;
	rect.h = 2;
	i = -1;
	while (++i < rt.scene.object_amount)
	{
		tmp = rect.y;
		rect.y -= rt.ui.objects.scrollbar.scroll / TILE;
		add_height = (rt.ui.objects.expanded[i] ? OBJECT_PROPERTIES_H : 0);
		if (rt.scene.objects[i].type &&
			rect.y + add_height >= rt.ui.objects.rect.y - TILE &&
			rect.y < rt.ui.objects.rect.y + rt.ui.objects.rect.h)
		{
			if (rt.ui.objects.expanded[i])
				ui_mouse_objectlist_expandedproperties(&rt.scene.objects[i], rect.y + 2);
			rect.x = 0;
			rect.w = UI_WIDTH_TILES - 4;
			if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
			{
				if (!(rt.input.keys & KEY_CTRL))
					ft_memclr(rt.ui.objects.selected, OBJECT_MAX_AMOUNT * sizeof(t_bool));
				rt.ui.objects.selected[i] = TRUE;
			}
			rect.x = UI_WIDTH_TILES - 4;
			rect.w = 2;
			if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
				rt.ui.objects.expanded[i] = !rt.ui.objects.expanded[i];
		}
		rect.y = tmp;
		rect.y += 2 + add_height;
	}
}
