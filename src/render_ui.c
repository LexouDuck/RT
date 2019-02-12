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

void	render_ui_menubar()
{
	t_u8		collided;
	SDL_Rect	rect;
	SDL_Point	mouse;
	t_s8		i;

	mouse.x = (rt.mouse.x) / TILE;
	mouse.y = (rt.mouse.y) / TILE;
	collided = 0;
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = rt.ui.menubar.item_hitbox[i];
		if (SDL_PointInRect(&mouse, &rect))
		{
			++collided;
			if (rt.mouse_button)
				rt.ui.menubar.selection = i;
		}
		render_ui_rect(rect, (collided == 1 ? ++collided : 0));
		render_ui_text(rt.ui.menubar.item_labels[i],
			rt.ui.menubar.item_hitbox[i].x + 2, 1, TRUE);
	}
	if (!collided && rt.mouse_button)
		rt.ui.menubar.selection = -1;
}

void	render_ui_dropdown(t_menu *dropdown)
{
	t_u8		collided;
	SDL_Rect	rect;
	SDL_Point	mouse;
	t_s8		i;

	mouse.x = (rt.mouse.x) / TILE;
	mouse.y = (rt.mouse.y) / TILE;
	collided = 0;
	i = -1;
	while (++i < dropdown->item_amount)
	{
		rect = dropdown->item_hitbox[i];
		if (SDL_PointInRect(&mouse, &rect))
		{
			++collided;
			if (rt.mouse_button)
				rt.ui.menubar.selection = i;
		}
		render_ui_rect(rect, (collided == 1 ? ++collided : 0));
		render_ui_text(dropdown->item_labels[i],
			2, 3 + 2 * i, TRUE);
	}
	if (!collided && rt.mouse_button)
		dropdown->selection = -1;
}
