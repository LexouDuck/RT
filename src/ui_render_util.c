/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 17:00:49 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

/*
**	Displays a rectangle of the given tile on the given tile region onscreen
*/

void		ui_render_fill(t_u8 tile_index,
	SDL_Rect dest_region, t_bool transparent)
{
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	static SDL_Rect	tile = {0, 0, TILE, TILE};
	t_s32			x;
	t_s32			y;

	if (transparent)
		SDL_SetColorKey(g_rt.ui.tileset, SDL_TRUE, g_rt.ui.pal[0]);
	tile.x = TILE * (tile_index % 16);
	tile.y = TILE * (tile_index / 16);
	y = -1;
	while (++y < dest_region.h)
	{
		x = -1;
		while (++x < dest_region.w)
		{
			dest.x = TILE * (dest_region.x + x);
			dest.y = TILE * (dest_region.y + y);
			if (SDL_BlitSurface(g_rt.ui.tileset, &tile,
				g_rt.sdl.display, &dest))
				debug_output_error("Error during ui_render_fill(): ", TRUE);
		}
	}
	if (transparent)
		SDL_SetColorKey(g_rt.ui.tileset, SDL_FALSE, g_rt.ui.pal[0]);
}

/*
**	Displays a 16x16 icon at the given tile coordinates
*/

void		ui_render_icon(t_u8 icon_index,
	t_s32 x, t_s32 y, t_bool transparent)
{
	static SDL_Rect	dest = {0, 0, TILE * 2, TILE * 2};
	static SDL_Rect	tile = {0, 0, TILE * 2, TILE * 2};

	if (transparent)
		SDL_SetColorKey(g_rt.ui.tileset, SDL_TRUE, g_rt.ui.pal[0]);
	tile.x = (TILE * 2) * (icon_index % 8);
	tile.y = (TILE * 2) * (icon_index / 8) + TILE * 8;
	dest.x = x;
	dest.y = y;
	if (SDL_BlitSurface(g_rt.ui.tileset, &tile, g_rt.sdl.display, &dest))
		debug_output_error("Error during ui_render_icon(): ", TRUE);
	if (transparent)
		SDL_SetColorKey(g_rt.ui.tileset, SDL_FALSE, g_rt.ui.pal[0]);
}

/*
**	Displays the given string in 8x8 monospace font at the given tile coords
*/

void		ui_render_text(char const *str,
	t_s32 x, t_s32 y, t_bool transparent)
{
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	static SDL_Rect	tile = {0, 0, TILE, TILE};
	size_t			i;

	if (str == NULL)
		str = "NULL";
	if (transparent)
		SDL_SetColorKey(g_rt.ui.tileset, SDL_TRUE, g_rt.ui.pal[0]);
	dest.x = TILE * x;
	dest.y = TILE * y;
	i = 0;
	while (str[i])
	{
		tile.x = ((t_u8)str[i] % 16) * TILE;
		tile.y = ((t_u8)str[i] / 16) * TILE;
		if (SDL_BlitSurface(g_rt.ui.tileset, &tile, g_rt.sdl.display, &dest))
			debug_output_error("Error during ui_render_text(): ", TRUE);
		dest.x += TILE;
		++i;
	}
	if (transparent)
		SDL_SetColorKey(g_rt.ui.tileset, SDL_FALSE, g_rt.ui.pal[0]);
}
