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

#include "libft_string.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "event.h"

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
		if (rt.scene.objects[i].type)
		{
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
			render_ui_icon((int)rt.scene.objects[i].type - 1,
				1, rect.y, TRUE);
			render_ui_text(/*rt.scene.objects[i].name*/NULL,
				4, rect.y + 1, TRUE);
			rect.y += 2;
		}
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
