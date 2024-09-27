/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render_util_rect.c                              :+:      :+:    :+:   */
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

static void	ui_render_rect_corners(SDL_Rect *rect, t_bool filled)
{
	static SDL_Rect rect_ul = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect rect_ur = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect rect_dl = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect rect_dr = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};

	rect_ul.x = TILE * (0x8 + (filled ? 4 : 0));
	rect_ur.x = TILE * (0xA + (filled ? 4 : 0));
	rect_dl.x = TILE * (0x9 + (filled ? 4 : 0));
	rect_dr.x = TILE * (0xB + (filled ? 4 : 0));
	dest.x = TILE * (rect->x);
	dest.y = TILE * (rect->y);
	if (SDL_BlitSurface(g_rt.ui.tileset, &rect_ul, g_rt.sdl.display, &dest))
		debug_output_error("Error during render_rect() -> UL corner: ", TRUE);
	dest.y = TILE * (rect->y + rect->h - 1);
	if (SDL_BlitSurface(g_rt.ui.tileset, &rect_dl, g_rt.sdl.display, &dest))
		debug_output_error("Error during render_rect() -> DL corner: ", TRUE);
	dest.x = TILE * (rect->x + rect->w - 1);
	dest.y = TILE * (rect->y);
	if (SDL_BlitSurface(g_rt.ui.tileset, &rect_ur, g_rt.sdl.display, &dest))
		debug_output_error("Error during render_rect() -> UR corner: ", TRUE);
	dest.x = TILE * (rect->x + rect->w - 1);
	dest.y = TILE * (rect->y + rect->h - 1);
	if (SDL_BlitSurface(g_rt.ui.tileset, &rect_dr, g_rt.sdl.display, &dest))
		debug_output_error("Error during render_rect() -> DR corner: ", TRUE);
}

static void	ui_render_rect_edges_h(SDL_Rect *rect, t_bool filled)
{
	static SDL_Rect	rect_u = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect	rect_d = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	int				i;

	rect_u.x = TILE * (0x9 + (filled ? 4 : 0));
	rect_d.x = TILE * (0xA + (filled ? 4 : 0));
	i = 0;
	while (++i < (rect->w - 1))
	{
		dest.x = TILE * (rect->x + i);
		dest.y = TILE * (rect->y);
		if (SDL_BlitSurface(g_rt.ui.tileset, &rect_u,
			g_rt.sdl.display, &dest))
			debug_output_error("Error during render_rect() -> U edge: ", TRUE);
	}
	i = 0;
	while (++i < (rect->w - 1))
	{
		dest.x = TILE * (rect->x + i);
		dest.y = TILE * (rect->y + rect->h - 1);
		if (SDL_BlitSurface(g_rt.ui.tileset, &rect_d,
			g_rt.sdl.display, &dest))
			debug_output_error("Error during render_rect() -> D edge: ", TRUE);
	}
}

static void	ui_render_rect_edges_v(SDL_Rect *rect, t_bool filled)
{
	static SDL_Rect	rect_r = { 0, TILE * 0, TILE, TILE };
	static SDL_Rect	rect_l = { 0, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	int				i;

	rect_l.x = TILE * (0x8 + (filled ? 4 : 0));
	rect_r.x = TILE * (0xB + (filled ? 4 : 0));
	i = 0;
	while (++i < (rect->h - 1))
	{
		dest.x = TILE * (rect->x);
		dest.y = TILE * (rect->y + i);
		if (SDL_BlitSurface(g_rt.ui.tileset, &rect_l,
			g_rt.sdl.display, &dest))
			debug_output_error("Error during render_rect() -> L edge: ", TRUE);
	}
	i = 0;
	while (++i < (rect->h - 1))
	{
		dest.x = TILE * (rect->x + rect->w - 1);
		dest.y = TILE * (rect->y + i);
		if (SDL_BlitSurface(g_rt.ui.tileset, &rect_r,
			g_rt.sdl.display, &dest))
			debug_output_error("Error during render_rect() -> R edge: ", TRUE);
	}
}

/*
**	Displays a HUD border rectangle of the given w,h (in tiles)
**	at the given tile x and y coordinates
*/

void		ui_render_rect(SDL_Rect rect, t_bool filled)
{
	static SDL_Rect	tile = {0, 0, TILE, TILE};
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	SDL_Point		i;

	ui_render_rect_corners(&rect, filled);
	ui_render_rect_edges_h(&rect, filled);
	ui_render_rect_edges_v(&rect, filled);
	i.x = 0;
	i.y = 0;
	tile.x = TILE * (filled ? 2 : 0);
	while (++i.y < rect.h - 1)
	{
		while (++i.x < rect.w - 1)
		{
			dest.x = TILE * (rect.x + i.x);
			dest.y = TILE * (rect.y + i.y);
			if (SDL_BlitSurface(g_rt.ui.tileset, &tile,
				g_rt.sdl.display, &dest))
				debug_output_error(
					"Error during ui_render_rect() -> center: ", TRUE);
		}
	}
}
