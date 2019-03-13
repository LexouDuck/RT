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

static void	ui_mouse_objectlist_expandedproperties(t_object *object, t_s32 y)
{
	cl_float3		*ptr;
	t_u8			i;

	if (ui_mouse_objectlist_expandedproperties_primitive(&object->type, y) ||
		ui_mouse_objectlist_expandedproperties_material(&object->material, y) ||
		ui_mouse_objectlist_expandedproperties_pattern(&object->pattern, y) ||
		ui_mouse_objectlist_expandedproperties_projection(&object->uvw_projection, y) ||
		ui_mouse_objectlist_expandedproperties_bump(&object->bump_type, y))
		return ;
	y += 10;
	ptr = &object->rgb_a;
	i = 0;
	while (i < OBJECT_PROPERTIES)
	{
		if (ui_mouse_control_numberbox_float(&rt.ui.current_textinput, &ptr->x, 1, y + 1) ||
			ui_mouse_control_numberbox_float(&rt.ui.current_textinput, &ptr->y, 10, y + 1) ||
			ui_mouse_control_numberbox_float(&rt.ui.current_textinput, &ptr->z, 19, y + 1))
			return ;
		y += OBJECT_PROPERTY_H;
		++ptr;
		++i;
	}
	update_object(object);
}

static void	ui_mouse_objectlist_object(SDL_Rect rect, t_u32 i, t_s32 height)
{
	if (rt.scene.objects[i].type &&
		rect.y + height >= rt.ui.objects.rect.y - TILE &&
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
}

void		ui_mouse_objectlist(void)
{
	t_s32		tmp;
	t_s32		add_height;
	SDL_Rect	rect;
	t_u32		i;

	rect = rt.ui.objects.rect;
	rect.h = 2;
	i = 0;
	while (i < rt.scene.object_amount)
	{
		tmp = rect.y;
		rect.y -= rt.ui.objects.scrollbar.scroll / TILE;
		add_height = (rt.ui.objects.expanded[i] ? OBJECT_PROPERTIES_H : 0);
		ui_mouse_objectlist_object(rect, i, add_height);
		rect.y = tmp;
		rect.y += 2 + add_height;
		++i;
	}
}
