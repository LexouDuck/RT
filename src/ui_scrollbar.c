/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_scrollbar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/03/11 15:05:24 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

inline void	ui_scrollbar_setscroll(t_scrollbar *scrollbar, t_s32 scroll)
{
	scrollbar->scroll += scroll;
	if (scroll < 0)
	{
		if (scrollbar->scroll < 0)
			scrollbar->scroll = 0;
	}
	if (scroll > 0)
	{
		if (scrollbar->scroll >
			(scrollbar->scroll_max - scrollbar->scroll_view + TILE))
			scrollbar->scroll =
			(scrollbar->scroll_max - scrollbar->scroll_view + TILE);
	}
}

void		ui_mouse_scrollbar(void)
{
	t_scrollbar	*scrollbar;
	t_s32		scrollbar_top;
	t_s32		scrollbar_bot;
	t_f32		ratio;

	scrollbar = &g_rt.ui.objects.scrollbar;
	if (SDL_PointInRect(&g_rt.input.mouse, &scrollbar->bar))
	{
		ratio = ((t_f32)scrollbar->bar.h / (t_f32)scrollbar->scroll_max);
		scrollbar_top = scrollbar->bar.y + (int)(scrollbar->scroll * ratio);
		scrollbar_bot = scrollbar_top + (int)(scrollbar->scroll_view * ratio);
		if (g_rt.input.mouse.y >= scrollbar_top &&
			g_rt.input.mouse.y <= scrollbar_bot)
			scrollbar->clicked = scrollclick_bar;
		else if (g_rt.input.mouse.y < scrollbar_top)
			scrollbar->clicked = scrollclick_bar_above;
		else if (g_rt.input.mouse.y > scrollbar_bot)
			scrollbar->clicked = scrollclick_bar_below;
	}
	else if (SDL_PointInRect(&g_rt.input.mouse, &scrollbar->button_up))
		scrollbar->clicked = scrollclick_button_up;
	else if (SDL_PointInRect(&g_rt.input.mouse, &scrollbar->button_down))
		scrollbar->clicked = scrollclick_button_down;
}

static void	ui_render_scrollbar_buttons(t_scrollbar *scrollbar)
{
	if (scrollbar->clicked == scrollclick_button_up)
		ui_scrollbar_setscroll(scrollbar, -1);
	if (scrollbar->clicked == scrollclick_button_down)
		ui_scrollbar_setscroll(scrollbar, +1);
	ui_render_icon((scrollbar->clicked == scrollclick_button_up ? 21 : 20),
		scrollbar->button_up.x,
		scrollbar->button_up.y, FALSE);
	ui_render_icon((scrollbar->clicked == scrollclick_button_down ? 29 : 28),
		scrollbar->button_down.x,
		scrollbar->button_down.y, FALSE);
}

static void	ui_render_scrollbar_bar(t_scrollbar *scrollbar,
	t_f32 ratio, SDL_Rect tile, SDL_Rect dest)
{
	t_s32			height;
	int				i;

	dest.y += (int)(scrollbar->scroll * ratio);
	if (SDL_BlitSurface(g_rt.ui.tileset, &tile, g_rt.sdl.display, &dest))
		debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
	dest.y += TILE;
	tile.y = TILE * 13;
	height = (scrollbar->scroll_view * ratio) / TILE - 2;
	i = -1;
	while (++i < height)
	{
		if (SDL_BlitSurface(g_rt.ui.tileset, &tile, g_rt.sdl.display, &dest))
			debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
		dest.y += TILE;
	}
	tile.y = TILE * 15;
	if (SDL_BlitSurface(g_rt.ui.tileset, &tile, g_rt.sdl.display, &dest))
		debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
	height = (scrollbar->scroll_view * ratio) / 2 - TILE / 2;
	dest.y = scrollbar->bar.y + (int)(scrollbar->scroll * ratio) + height;
	tile.y = TILE * 14;
	if (SDL_BlitSurface(g_rt.ui.tileset, &tile, g_rt.sdl.display, &dest))
		debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
}

void		ui_render_scrollbar(t_scrollbar *scrollbar)
{
	static SDL_Rect	dest = { 0, 0, TILE / 2, TILE * 2 };
	static SDL_Rect	tile = { 0, 0, TILE * 2, TILE };
	t_f32			ratio;

	ui_render_scrollbar_buttons(scrollbar);
	tile.x = TILE *
		(g_rt.ui.objects.scrollbar.clicked == scrollclick_bar ? 14 : 12);
	tile.y = TILE * 12;
	dest.x = scrollbar->bar.x;
	dest.y = scrollbar->bar.y;
	ratio = (scrollbar->bar.h / (t_f32)scrollbar->scroll_max);
	ui_render_scrollbar_bar(scrollbar, ratio, tile, dest);
}
