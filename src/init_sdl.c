/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_sdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"
#include "../rt.h"
#include "config.h"
#include "debug.h"

int			init_sdl(void)
{
	if (SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_VIDEO) < 0)
	{
		debug_output_error("Could not initialize SDL2: ", TRUE);
		return (ERROR);
	}
	return (OK);
}

static void	init_window_checksize(int *window_w, int *window_h)
{
	if (*window_w < UI_WIDTH + 32)
		*window_w = UI_WIDTH + 32;
	if (*window_w > 3840)
		*window_w = 3840;
	if (*window_h < 32)
		*window_h = 32;
	if (*window_h > 2160)
		*window_h = 2160;
}

int			init_window(void)
{
	t_u32	flags;

	g_rt.sdl.window_w = ft_str_to_s32(config_get(CONFIG_INDEX_WINDOW_W));
	g_rt.sdl.window_h = ft_str_to_s32(config_get(CONFIG_INDEX_WINDOW_H));
	init_window_checksize(&g_rt.sdl.window_w, &g_rt.sdl.window_h);
	flags = (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (ft_str_to_bool(config_get(CONFIG_INDEX_FULLSCREEN)))
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (ft_str_to_bool(config_get(CONFIG_INDEX_MAXIMIZED)))
		flags |= SDL_WINDOW_MAXIMIZED;
	g_rt.sdl.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, g_rt.sdl.window_w, g_rt.sdl.window_h, flags);
	if (g_rt.sdl.window == NULL)
	{
		debug_output_error("Could not create SDL_Window: ", TRUE);
		return (ERROR);
	}
	g_rt.sdl.window_renderer = SDL_CreateRenderer(g_rt.sdl.window, -1, 0);
	if (g_rt.sdl.window_renderer == NULL)
	{
		debug_output_error("Could not create SDL_Renderer: ", TRUE);
		return (ERROR);
	}
	return (OK);
}

int			init_window_display_canvas(void)
{
	g_rt.canvas_w = (g_rt.sdl.window_w - UI_WIDTH);
	g_rt.canvas_h = (g_rt.sdl.window_h);
	g_rt.canvas_pixel_amount = (g_rt.canvas_w * g_rt.canvas_h);
	g_rt.canvas = SDL_CreateRGBSurfaceWithFormat(
		SDL_RLEACCEL,
		g_rt.canvas_w, g_rt.canvas_h,
		8, SDL_PIXELFORMAT_ARGB8888);
	if (g_rt.canvas == NULL)
	{
		debug_output_error("Could not create the render canvas: ", TRUE);
		return (ERROR);
	}
	return (OK);
}

int			init_window_display(void)
{
	SDL_GetWindowSize(g_rt.sdl.window, &g_rt.sdl.window_w, &g_rt.sdl.window_h);
	init_window_checksize(&g_rt.sdl.window_w, &g_rt.sdl.window_h);
	SDL_SetWindowSize(g_rt.sdl.window, g_rt.sdl.window_w, g_rt.sdl.window_h);
	g_rt.sdl.window_texture = SDL_CreateTexture(g_rt.sdl.window_renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		g_rt.sdl.window_w,
		g_rt.sdl.window_h);
	if (g_rt.sdl.window_texture == NULL)
	{
		debug_output_error("Could not create window's SDL_Texture: ", TRUE);
		return (ERROR);
	}
	g_rt.sdl.display = SDL_CreateRGBSurfaceWithFormat(
		SDL_RLEACCEL,
		g_rt.sdl.window_w, g_rt.sdl.window_h,
		8, SDL_PIXELFORMAT_ARGB8888);
	if (g_rt.sdl.display == NULL)
	{
		debug_output_error("Could not create window's SDL_Surface: ", TRUE);
		return (ERROR);
	}
	return (init_window_display_canvas());
}
