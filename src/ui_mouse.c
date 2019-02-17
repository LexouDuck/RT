/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

#include "../rt.h"
#include "debug.h"

void	ui_mouse_objectlist()
{
	SDL_Rect	rect;
	t_s8		i;

	rect.x = 0;
	rect.y = 4;
	rect.w = UI_WIDTH_TILES - 1;
	rect.h = 2;
	i = -1;
	while (++i < OBJECT_MAX_AMOUNT)
	{
		if (rt.scene.objects[i].type == none)
			continue ;
		if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
		{
			if (!(rt.input.keys & KEY_CTRL))
				ft_memclr(rt.ui.objects_selected,
					OBJECT_MAX_AMOUNT * sizeof(t_bool));
			rt.ui.objects_selected[i] = TRUE;
		}
		rect.y += 2;
	}
}

void	ui_mouse_menubar()
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
				rt.ui.menubar.selection = i;
				collided = TRUE;
			}
		}
		if (!collided)
			dropdown->selection = -1;
	}
}
