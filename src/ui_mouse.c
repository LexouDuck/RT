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

void	ui_mouse_objectlist_expandedproperties(t_object *object, t_s32 y)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };
	cl_float3		*ptr;
	t_u8			i;

	rect.x = 11;
	rect.y = y + 1;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		object->material = (int)object->material == 0 ? 3 : object->material - 1;
		rt.must_render = TRUE;
		return ;
	}
	rect.x = 25;
	rect.y = y + 1;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		object->material = (int)object->material == 3 ? 0 : object->material + 1;
		rt.must_render = TRUE;
		return ;
	}
	y += 4;
	ptr = &object->rgb;
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
}

void	ui_mouse_objectlist(void)
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

void	ui_mouse_menubar(void)
{
	t_bool		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = FALSE;
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = rt.ui.menubar.item_hitbox[i];
		if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
		{
			rt.ui.menubar.selection = i;
			collided = TRUE;
		}
	}
	if (!collided)
		rt.ui.menubar.selection = -1;
}

void	ui_mouse_dropdown(t_menu *dropdown)
{
	t_bool		collided;
	SDL_Rect	rect;
	t_s8		i;

	if (dropdown && rt.ui.menubar.selection != -1)
	{
		collided = FALSE;
		i = -1;
		while (++i < dropdown->item_amount)
		{
			rect = dropdown->item_hitbox[i];
			if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
			{
				if (dropdown->item_action[i])
					dropdown->item_action[i]();
				collided = TRUE;
			}
		}
		if (!collided)
			dropdown->selection = -1;
	}
}
