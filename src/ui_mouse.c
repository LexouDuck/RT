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

#include "../rt.h"
#include "debug.h"

void			ui_mouse_menubar(void)
{
	t_bool		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = FALSE;
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = g_rt.ui.menubar.item_hitbox[i];
		if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
		{
			g_rt.ui.menubar.selection = i;
			collided = TRUE;
		}
	}
	if (!collided)
		g_rt.ui.menubar.selection = -1;
	return ;
}

void			ui_mouse_dropdown(t_menu *dropdown)
{
	t_bool		collided;
	SDL_Rect	rect;
	t_s8		i;

	if (dropdown && g_rt.ui.menubar.selection != -1)
	{
		collided = FALSE;
		i = -1;
		while (++i < dropdown->item_amount)
		{
			rect = dropdown->item_hitbox[i];
			if (SDL_PointInRect(&g_rt.input.mouse_tile, &rect))
			{
				if (dropdown->item_action[i])
					dropdown->item_action[i]();
				collided = TRUE;
			}
		}
		if (!collided)
			dropdown->selection = -1;
	}
	return ;
}
