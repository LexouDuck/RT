/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

/*
**	Displays a rectangle of the given tile on the given tile region onscreen
*/
void	render_ui_fill(t_u8 tile_index,
	SDL_Rect dest_region, t_bool transparent)
{
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	static SDL_Rect	tile = {0, 0, TILE, TILE};
	t_s32			x;
	t_s32			y;

	if (transparent)
		SDL_SetColorKey(rt.ui.tileset, SDL_TRUE, rt.ui.pal[0]);
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
			if (SDL_BlitSurface(rt.ui.tileset, &tile,
				rt.sdl.window_surface, &dest))
				debug_output_error("Error during render_text(): ", TRUE);
		}
	}
	if (transparent)
		SDL_SetColorKey(rt.ui.tileset, SDL_FALSE, rt.ui.pal[0]);
}

/*
**	Displays a 16x16 icon at the given tile coordinates
*/
void	render_ui_icon(t_u8 icon_index,
	t_s32 x, t_s32 y, t_bool transparent)
{
	static SDL_Rect	dest = {0, 0, TILE * 2, TILE * 2};
	static SDL_Rect	tile = {0, 0, TILE * 2, TILE * 2};

	if (transparent)
		SDL_SetColorKey(rt.ui.tileset, SDL_TRUE, rt.ui.pal[0]);
	tile.x = (TILE * 2) * (icon_index % 8);
	tile.y = (TILE * 2) * (icon_index / 8) + TILE * 8;
	dest.x = TILE * x;
	dest.y = TILE * y;
	if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_text(): ", TRUE);
	if (transparent)
		SDL_SetColorKey(rt.ui.tileset, SDL_FALSE, rt.ui.pal[0]);
}

/*
**	Displays the given string in 8x8 monospace font at the given tile coords
*/
void		render_ui_text(char const* str,
	t_s32 x, t_s32 y, t_bool transparent)
{
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	static SDL_Rect	tile = {0, 0, TILE, TILE};
	size_t			i;

	if (str == NULL)
		str = "NULL";
	if (transparent)
		SDL_SetColorKey(rt.ui.tileset, SDL_TRUE, rt.ui.pal[0]);
	dest.x = TILE * x;
	dest.y = TILE * y;
	i = 0;
	while (str[i])
	{
		tile.x = (str[i] % 16) * TILE;
		tile.y = (str[i] / 16) * TILE;
		if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_text(): ", TRUE);
		dest.x += TILE;
		++i;
	}
	if (transparent)
		SDL_SetColorKey(rt.ui.tileset, SDL_FALSE, rt.ui.pal[0]);
}

static void	render_ui_rect_corners(SDL_Rect *rect, t_bool filled)
{
	static SDL_Rect rect_UL = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect rect_UR = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect rect_DL = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect rect_DR = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};

	rect_UL.x = TILE * (0x8 + (filled ? 4 : 0));
	rect_UR.x = TILE * (0xA + (filled ? 4 : 0));
	rect_DL.x = TILE * (0x9 + (filled ? 4 : 0));
	rect_DR.x = TILE * (0xB + (filled ? 4 : 0));
	// UL corner
	dest.x = TILE * (rect->x);
	dest.y = TILE * (rect->y);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_UL, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> UL corner: ", TRUE);
	// DL corner
	dest.y = TILE * (rect->y + rect->h - 1);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_DL, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> DL corner: ", TRUE);
	// UR corner
	dest.x = TILE * (rect->x + rect->w - 1);
	dest.y = TILE * (rect->y);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_UR, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> UR corner: ", TRUE);
	// DR corner
	dest.x = TILE * (rect->x + rect->w - 1);
	dest.y = TILE * (rect->y + rect->h - 1);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_DR, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> DR corner: ", TRUE);
}

static void	render_ui_rect_edges_h(SDL_Rect *rect, t_bool filled)
{
	static SDL_Rect	rect_U = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect	rect_D = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	int				i;

	rect_U.x = TILE * (0x9 + (filled ? 4 : 0));
	rect_D.x = TILE * (0xA + (filled ? 4 : 0));
	i = 1; // U edge
	while (i < (rect->w - 1))
	{
		dest.x = TILE * (rect->x + i);
		dest.y = TILE * (rect->y);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_U, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> U edge: ", TRUE);
		++i;
	}
	i = 1; // D edge
	while (i < (rect->w - 1))
	{
		dest.x = TILE * (rect->x + i);
		dest.y = TILE * (rect->y + rect->h - 1);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_D, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> D edge: ", TRUE);
		++i;
	}
}

static void	render_ui_rect_edges_v(SDL_Rect *rect, t_bool filled)
{
	static SDL_Rect	rect_R = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect	rect_L = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	int				i;

	rect_L.x = TILE * (0x8 + (filled ? 4 : 0));
	rect_R.x = TILE * (0xB + (filled ? 4 : 0));
	i = 1; // L edge
	while (i < (rect->h - 1))
	{
		dest.x = TILE * (rect->x);
		dest.y = TILE * (rect->y + i);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_L, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> L edge: ", TRUE);
		++i;
	}
	i = 1; // R edge
	while (i < (rect->h - 1))
	{
		dest.x = TILE * (rect->x + rect->w - 1);
		dest.y = TILE * (rect->y + i);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_R, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> R edge: ", TRUE);
		++i;
	}
}

/*
**	Displays a HUD border rectangle of the given w,h (in tiles)
**	at the given tile x and y coordinates
*/
void	render_ui_rect(SDL_Rect rect, t_bool filled)
{
	static SDL_Rect	tile = {0, 0, TILE, TILE};
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	SDL_Point		i;

	render_ui_rect_corners(&rect, filled);
	render_ui_rect_edges_h(&rect, filled);
	render_ui_rect_edges_v(&rect, filled);
	i.x = 0;
	i.y = 0;
	tile.x = TILE * (filled ? 2 : 0);
	while (++i.y < rect.h - 1)
		while (++i.x < rect.w - 1)
		{
			dest.x = TILE * (rect.x + i.x);
			dest.y = TILE * (rect.y + i.y);
			if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
				debug_output_error(
					"Error during render_rect() -> center: ", TRUE);
		}
}
