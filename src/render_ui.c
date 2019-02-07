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

/*
**	Displays the given string in 8x8 monospace font at the given coordinates
*/
void		render_ui_text(
	char const* str,
	t_s32 x,
	t_s32 y,
	t_bool colored)
{
	static SDL_Rect	dest = {0, 0, TILE, TILE};
	static SDL_Rect	tile = {0, 0, TILE, TILE};

	if (str)
	{
		dest.x = TILE * x;
		dest.y = TILE * y;
		for (size_t i = 0; str[i]; ++i)
		{
			tile.x = (str[i] % 16) * TILE;
			tile.y = (str[i] / 16) * TILE + (colored ? 8 * TILE : 0);
			if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
				debug_output_error("Error during render_text(): ", TRUE);
			dest.x += TILE;
		}
	}
}

static void	render_ui_rect_corners(t_s32 x, t_s32 y, t_u8 w, t_u8 h)
{
	static const SDL_Rect rect_UL = { TILE * 4, TILE * 0, TILE, TILE };
	static const SDL_Rect rect_UR = { TILE * 6, TILE * 0, TILE, TILE };
	static const SDL_Rect rect_DL = { TILE * 5, TILE * 1, TILE, TILE };
	static const SDL_Rect rect_DR = { TILE * 7, TILE * 1, TILE, TILE };
	static SDL_Rect	dest = {0, 0, TILE, TILE};

	// UL corner
	dest.x = TILE * (x);
	dest.y = TILE * (y);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_UL, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> UL corner: ", TRUE);
	// UR corner
	dest.x = TILE * (x + w - 1);
	dest.y = TILE * (y);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_UR, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> UR corner: ", TRUE);
	// DL corner
	dest.x = TILE * (x);
	dest.y = TILE * (y + h - 1);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_DL, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> DL corner: ", TRUE);
	// DR corner
	dest.x = TILE * (x + w - 1);
	dest.y = TILE * (y + h - 1);
	if (SDL_BlitSurface(rt.ui.tileset, &rect_DR, rt.sdl.window_surface, &dest))
		debug_output_error("Error during render_rect() -> DR corner: ", TRUE);
}

static void	render_ui_rect_edges_h(t_s32 x, t_s32 y, t_u8 w, t_u8 h)
{
	static const SDL_Rect	rect_U  = { TILE * 5, TILE * 0, TILE, TILE };
	static const SDL_Rect	rect_D  = { TILE * 6, TILE * 1, TILE, TILE };
	static SDL_Rect			dest = {0, 0, TILE, TILE};
	int						i;

	i = 1; // U edge
	while (i < (w - 1))
	{
		dest.x = TILE * (x + i);
		dest.y = TILE * (y);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_U, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> U edge: ", TRUE);
		++i;
	}
	i = 1; // D edge
	while (i < (w - 1))
	{
		dest.x = TILE * (x + i);
		dest.y = TILE * (y + h - 1);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_D, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> D edge: ", TRUE);
		++i;
	}
}

static void	render_ui_rect_edges_v(t_s32 x, t_s32 y, t_u8 w, t_u8 h)
{
	static const SDL_Rect	rect_R  = { TILE * 7, TILE * 0, TILE, TILE };
	static const SDL_Rect	rect_L  = { TILE * 4, TILE * 1, TILE, TILE };
	static SDL_Rect			dest = {0, 0, TILE, TILE};
	int						i;

	i = 1;// L edge
	while (i < (h - 1))
	{
		dest.x = TILE * (x);
		dest.y = TILE * (y + i);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_L, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> L edge: ", TRUE);
		++i;
	}
	i = 1;// R edge
	while (i < (h - 1))
	{
		dest.x = TILE * (x + w - 1);
		dest.y = TILE * (y + i);
		if (SDL_BlitSurface(rt.ui.tileset, &rect_R, rt.sdl.window_surface, &dest))
			debug_output_error("Error during render_rect() -> R edge: ", TRUE);
		++i;
	}
}

/*
**	Displays a HUD border rectangle of the given w,h at the given coordinates
*/
void	render_ui_rect(t_s32 x, t_s32 y, t_u8 w, t_u8 h)
{
	static const SDL_Rect	tile = {0, 0, TILE, TILE};
	static SDL_Rect			dest = {0, 0, TILE, TILE};
	SDL_Point				i;

	render_ui_rect_corners(x, y, w, h);
	render_ui_rect_edges_h(x, y, w, h);
	render_ui_rect_edges_v(x, y, w, h);
	i.x = 0;
	i.y = 0;
	while (++i.y < h - 1)
		while (++i.x < w - 1)
		{
			dest.x = TILE * (x + i.x);
			dest.y = TILE * (y + i.y);
			if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
				debug_output_error(
					"Error during render_rect() -> center: ", TRUE);
		}
}

void	render_ui_menubar()
{
	t_u8		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = 0;
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = rt.ui.menubar.item_hitbox[i];
		render_ui_rect(rect.x, rect.y, rect.w, rect.h);
		rect.x *= TILE;
		rect.y *= TILE;
		rect.w *= TILE;
		rect.h *= TILE;
		if (SDL_PointInRect(&rt.mouse, &rect))
		{
			++collided;
			if (rt.mouse_button)
				rt.ui.menubar.selection = i;
		}
		render_ui_text(rt.ui.menubar.item_labels[i],
			rt.ui.menubar.item_hitbox[i].x + 2, 1, (collided == 1 ? ++collided : 0));
	}
	if (!collided && rt.mouse_button)
		rt.ui.menubar.selection = -1;
}

void	render_ui_dropdown(t_menu *dropdown)
{
	t_u8		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = 0;
	i = -1;
	while (++i < dropdown->item_amount)
	{
		rect = dropdown->item_hitbox[i];
		render_ui_rect(rect.x, rect.y, rect.w, rect.h);
		rect.x *= TILE;
		rect.y *= TILE;
		rect.w *= TILE;
		rect.h *= TILE;
		if (SDL_PointInRect(&rt.mouse, &rect))
		{
			++collided;
			if (rt.mouse_button)
				rt.ui.menubar.selection = i;
		}
		render_ui_text(dropdown->item_labels[i],
			2, 3 + 2 * i, (collided == 1 ? ++collided : 0));
	}
	if (!collided && rt.mouse_button)
		dropdown->selection = -1;
}
