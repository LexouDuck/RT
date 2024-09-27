/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouse_objectlist.c                              :+:      :+:    :+:   */
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

static t_bool	ui_mouse_objectlist_expandedproperties_enums(
	t_object *object, t_s32 y)
{
	if (ui_mouse_objectlist_expandedproperties_primitive(&object->type, y))
		return (TRUE);
	if (ui_mouse_objectlist_expandedproperties_material(&object->material, y))
		return (TRUE);
	if (ui_mouse_objectlist_expandedproperties_pattern(&object->pattern, y))
		return (TRUE);
	if (ui_mouse_objectlist_expandedproperties_projection(
		&object->uvw_projection, y))
		return (TRUE);
	if (ui_mouse_objectlist_expandedproperties_bump(&object->bump_type, y))
		return (TRUE);
	return (FALSE);
}

static void		ui_mouse_objectlist_expandedproperties(
	t_object *object, t_s32 y)
{
	cl_float3		*ptr;
	t_u8			i;

	if (ui_mouse_objectlist_expandedproperties_enums(object, y))
		return ;
	y += 10;
	ptr = &object->rgb_a;
	i = 0;
	while (i < OBJECT_PROPERTIES)
	{
		if (ui_mouse_control_numberbox_float(
				&g_rt.ui.current_textinput, &ptr->x, 1, y + 1) ||
			ui_mouse_control_numberbox_float(
				&g_rt.ui.current_textinput, &ptr->y, 10, y + 1) ||
			ui_mouse_control_numberbox_float(
				&g_rt.ui.current_textinput, &ptr->z, 19, y + 1))
			return ;
		y += OBJECT_PROPERTY_H;
		++ptr;
		++i;
	}
	update_object(object);
}

static void		ui_mouse_objectlist_object(SDL_Rect rect, t_u32 i, t_s32 height)
{
	if (g_rt.scene.objects[i].type &&
		rect.y + height >= g_rt.ui.objects.rect.y - TILE &&
		rect.y < g_rt.ui.objects.rect.y + g_rt.ui.objects.rect.h)
	{
		if (g_rt.ui.objects.expanded[i])
			ui_mouse_objectlist_expandedproperties(
				&g_rt.scene.objects[i], rect.y + 2);
		rect.x = 0;
		rect.w = UI_WIDTH_TILES - 4;
		if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
		{
			if (!(g_rt.input.keys & KEY_CTRL || g_rt.input.keys & KEY_SHIFT))
				ft_memclr(g_rt.ui.objects.selected,
					sizeof(t_bool) * OBJECT_MAX_AMOUNT);
			g_rt.ui.objects.selected[i] = TRUE;
		}
		rect.x = UI_WIDTH_TILES - 4;
		rect.w = 2;
		if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
			g_rt.ui.objects.expanded[i] = !g_rt.ui.objects.expanded[i];
	}
}

void			ui_mouse_objectlist(void)
{
	t_s32		tmp;
	t_s32		add_height;
	SDL_Rect	rect;
	t_u32		i;

	rect = g_rt.ui.objects.rect;
	rect.h = 2;
	i = 0;
	while (i < g_rt.scene.object_amount)
	{
		tmp = rect.y;
		rect.y -= g_rt.ui.objects.scrollbar.scroll / TILE;
		add_height = (g_rt.ui.objects.expanded[i] ? OBJECT_PROPERTIES_H : 0);
		ui_mouse_objectlist_object(rect, i, add_height);
		rect.y = tmp;
		rect.y += 2 + add_height;
		++i;
	}
}
