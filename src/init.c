/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
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

int		init_sdl()
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

int		init_window()
{
	t_s32 window_w;
	t_s32 window_h;
	t_u32 flags;

	window_w = FT_String_To_S32(config_get(CONFIG_INDEX_WINDOW_W));
	window_h = FT_String_To_S32(config_get(CONFIG_INDEX_WINDOW_H));
	flags = (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (FT_String_To_Bool(config_get(CONFIG_INDEX_FULLSCREEN)))
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (FT_String_To_Bool(config_get(CONFIG_INDEX_MAXIMIZED)))
		flags |= SDL_WINDOW_MAXIMIZED;
	rt.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, window_w, window_h, flags);
	if (rt.window == NULL)
	{
		debug_output_error("Could not create SDL_Window: ", TRUE);
		return (ERROR);
	}
	rt.window_renderer = SDL_CreateRenderer(rt.window, -1, 0);
	if (rt.window_renderer == NULL)
	{
		debug_output_error("Could not create SDL_Renderer: ", TRUE);
		return (ERROR);
	}
	return (OK);
}

int		init_screen()
{
	t_s32 window_w;
	t_s32 window_h;

	SDL_GetWindowSize(rt.window, &window_w, &window_h);
	rt.window_texture = SDL_CreateTexture(rt.window_renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_w,
		window_h);
	if (rt.window_texture == NULL)
	{
		debug_output_error("Could not create window's SDL_Texture: ", TRUE);
		return (ERROR);
	}
	rt.window_surface = SDL_CreateRGBSurfaceWithFormat(
		SDL_RLEACCEL,
		window_w, window_h,
		8, SDL_PIXELFORMAT_ARGB8888);
	if (rt.window_surface == NULL)
	{
		debug_output_error("Could not create window's SDL_Surface: ", TRUE);
		return (ERROR);
	}
	return (OK);
}
