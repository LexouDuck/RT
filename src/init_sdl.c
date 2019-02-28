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

int		init_sdl(void)
{
	if (SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_VIDEO |
		SDL_INIT_AUDIO) < 0)
	{
		debug_output_error("Could not initialize SDL2: ", TRUE);
		return (ERROR);
	}
	return (OK);
}

int		init_window(void)
{
	t_u32	flags;

	rt.sdl.window_w = FT_String_To_S32(config_get(CONFIG_INDEX_WINDOW_W));
	rt.sdl.window_h = FT_String_To_S32(config_get(CONFIG_INDEX_WINDOW_H));
	flags = (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (FT_String_To_Bool(config_get(CONFIG_INDEX_FULLSCREEN)))
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (FT_String_To_Bool(config_get(CONFIG_INDEX_MAXIMIZED)))
		flags |= SDL_WINDOW_MAXIMIZED;
	rt.sdl.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, rt.sdl.window_w, rt.sdl.window_h, flags);
	if (rt.sdl.window == NULL)
	{
		debug_output_error("Could not create SDL_Window: ", TRUE);
		return (ERROR);
	}
	rt.sdl.window_renderer = SDL_CreateRenderer(rt.sdl.window, -1, 0);
	if (rt.sdl.window_renderer == NULL)
	{
		debug_output_error("Could not create SDL_Renderer: ", TRUE);
		return (ERROR);
	}
	return (OK);
}

int		init_window_display(void)
{
	SDL_GetWindowSize(rt.sdl.window, &rt.sdl.window_w, &rt.sdl.window_h);
	rt.sdl.window_texture = SDL_CreateTexture(rt.sdl.window_renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		rt.sdl.window_w,
		rt.sdl.window_h);
	if (rt.sdl.window_texture == NULL)
	{
		debug_output_error("Could not create window's SDL_Texture: ", TRUE);
		return (ERROR);
	}
	rt.sdl.window_surface = SDL_CreateRGBSurfaceWithFormat(
		SDL_RLEACCEL,
		rt.sdl.window_w, rt.sdl.window_h,
		8, SDL_PIXELFORMAT_ARGB8888);
	if (rt.sdl.window_surface == NULL)
	{
		debug_output_error("Could not create window's SDL_Surface: ", TRUE);
		return (ERROR);
	}
	rt.canvas_w = (rt.sdl.window_w - UI_WIDTH);
	rt.canvas_h = (rt.sdl.window_h);
	rt.canvas_pixel_amount = (rt.canvas_w * rt.canvas_h);
	rt.canvas = SDL_CreateRGBSurfaceWithFormat(
		SDL_RLEACCEL,
		rt.canvas_w, rt.canvas_h,
		8, SDL_PIXELFORMAT_ARGB8888);
	if (rt.canvas == NULL)
	{
		debug_output_error("Could not create window's SDL_Surface: ", TRUE);
		return (ERROR);
	}
	return (OK);
}
