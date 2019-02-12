/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_convert.h"
#include "libft_color.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "event.h"

void	render_ui_icon_object(t_object* object, t_s32 y)
{
	static t_u32	palette[PALETTE] = {
		0x000000,
		0x0058F8,
		0x3CBCFC,
		0xFCFCFC
	};

	if (object->type == none)
		return ;
	palette[2] = object->color;
	palette[1] = palette[2];
	palette[1] = (ft_color_argb32_get_r(palette[1]) < 0x30) ? (palette[1] & 0x00FFFF) : (palette[1] - 0x300000);
	palette[1] = (ft_color_argb32_get_g(palette[1]) < 0x30) ? (palette[1] & 0xFF00FF) : (palette[1] - 0x003000);
	palette[1] = (ft_color_argb32_get_b(palette[1]) < 0x30) ? (palette[1] & 0xFFFF00) : (palette[1] - 0x000030);
	if (!ui_set_palette(rt.ui.tileset, palette))
		return ;
	render_ui_icon((int)object->type - 1, 1, y, TRUE);
	if (!ui_set_palette(rt.ui.tileset, rt.ui.pal))
		return ;
}

void	render_ui_objects(SDL_Point* mouse_tile)
{
	SDL_Rect	rect;
	t_s32		i;

	rect.x = 0;
	rect.y = 4;
	rect.w = UI_WIDTH_TILES - 1;
	rect.h = 2;
	i = -1;
	while (++i < OBJECT_MAX_AMOUNT)
	{
		if (rt.scene.objects[i].type == none)
			continue ;
		if (rt.ui.objects_selected[i])
			render_ui_fill(2, rect, FALSE);
		else if (SDL_PointInRect(mouse_tile, &rect))
		{
			render_ui_fill(1, rect, FALSE);
			if (rt.input.mouse_button)
			{
				if (!(rt.input.keys & KEY_CTRL))
					ft_memclr(rt.ui.objects_selected,
						OBJECT_MAX_AMOUNT * sizeof(t_bool));
				rt.ui.objects_selected[i] = TRUE;
			}
		}
		render_ui_icon_object(&rt.scene.objects[i], rect.y);
		render_ui_text(/*rt.scene.objects[i].name*/NULL, 4, rect.y + 1, TRUE);
		render_ui_text((rt.ui.objects_expanded[i] ? "\xFE" : "\xFF"),
			UI_WIDTH_TILES - 3, rect.y + 1, TRUE);
		rect.y += 2;
	}
}

void	render_ui_menubar(SDL_Point* mouse_tile)
{
	t_u8		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = 0;
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = rt.ui.menubar.item_hitbox[i];
		if (SDL_PointInRect(mouse_tile, &rect))
		{
			++collided;
			if (rt.input.mouse_button)
				rt.ui.menubar.selection = i;
		}
		render_ui_rect(rect, (collided == 1 ? ++collided : 0));
		render_ui_text(rt.ui.menubar.item_labels[i],
			rt.ui.menubar.item_hitbox[i].x + 2, 1, TRUE);
	}
	if (!collided && rt.input.mouse_button)
		rt.ui.menubar.selection = -1;
}

void	render_ui_dropdown(SDL_Point* mouse_tile, t_menu *dropdown)
{
	t_u8		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = 0;
	i = -1;
	while (++i < dropdown->item_amount)
	{
		rect = dropdown->item_hitbox[i];
		if (SDL_PointInRect(mouse_tile, &rect))
		{
			++collided;
			if (rt.input.mouse_button)
				rt.ui.menubar.selection = i;
		}
		render_ui_rect(rect, (collided == 1 ? ++collided : 0));
		render_ui_text(dropdown->item_labels[i],
			2, 3 + 2 * i, TRUE);
	}
	if (!collided && rt.input.mouse_button)
		dropdown->selection = -1;
}
