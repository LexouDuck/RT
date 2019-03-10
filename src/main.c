/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../assets.h"
#include "../rt.h"
#include "config.h"
#include "debug.h"
#include "event.h"
#include "ui.h"
#include "rt_scene.h"

static void		update_window(void)
{
	SDL_Rect	dest;

	// Fill the window pixel buffer with black
	if (SDL_FillRect(rt.sdl.window_surface, NULL, 0x000000))
		debug_output_error(
			"Error during update_window() -> Screen clear: ", TRUE);
	// display the UI
	if (rt.ui.current_prompt.name)
		ui_render_prompt();
	else
	{
		ui_render_objectlist();
		ui_render_menubar();
	}
	if (rt.ui.menubar.selection != -1)
		ui_render_dropdown(&rt.ui.dropdowns[rt.ui.menubar.selection]);
	if (rt.must_render)
	{
	// Do the 3d render if needed
		render();//TODO: thread call to render with an SDL call ?
	}
	dest = rt.sdl.window_surface->clip_rect;
	dest.x += UI_WIDTH;
	dest.w -= UI_WIDTH;
	if (SDL_BlitSurface(rt.canvas, &rt.canvas->clip_rect, rt.sdl.window_surface, &dest))
		debug_output_error("Error during update_window() -> render blit: ", TRUE);
	ui_render_caminfo(&rt.scene.camera);
	ui_render_loading_bar();//TODO SNIF
	if (SDL_UpdateTexture(rt.sdl.window_texture, NULL,
		rt.sdl.window_surface->pixels, rt.sdl.window_surface->pitch))
	{ // and update the window display
		debug_output_error("Error during window update: ", TRUE);
	}
	//	if (SDL_RenderClear(rt.sdl.window_renderer))
	//		debug_output_error("Error during render screen clear: ", TRUE);
	if (SDL_RenderCopy(rt.sdl.window_renderer, rt.sdl.window_texture, NULL, NULL))
		debug_output_error("Error during render copy: ", TRUE);
	SDL_RenderPresent(rt.sdl.window_renderer);
	rt.must_render = FALSE;
}

static void		main_exit(void)
{
	if (rt.ui.current_textinput.input)
	{
		free(rt.ui.current_textinput.input);
		rt.ui.current_textinput.input = NULL;
	}
	config_save();
	config_free();
	opencl_freeall();
	SDL_DestroyWindow(rt.sdl.window);
	SDL_Quit();
}

/*
**	The main program loop: pretty much everything is called from here
**	Runs at 60fps (the 3 first lines of code inside the loop do this)
*/

static int		main_loop(void)
{
	t_u32	frame_wait;

	frame_wait = 0;
	rt.sdl.current_frame = 0;
	rt.must_render = TRUE;
	rt.sdl.loop = TRUE;
	while (rt.sdl.loop)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), frame_wait))
			SDL_Delay(1);
		frame_wait = SDL_GetTicks() + FRAME_MS;
		++rt.sdl.current_frame;
		event_checkevents();
		update_window();
	}
	debug_output("Attempting to close program...\n");
	main_exit();
	debug_output("Program closed successfully.\n");
	return (OK);
}

static void		main_check_args()
{
	int	i;

	if (argc > 1)
	{
		i = 1;
		rt.filepath = argv[i];
		rt_file_open(rt.filepath);
		while (++i < argc)
		{
			rt.filepath = NULL;
			rt_file_import(argv[i]);
		}
	}
}

/*
**	This is for windows compatibility, so as to have the 'main' entry point
**	rather than the native 'WinMain' function for windows GUI programs.
**	Basically what this code does is that if 'main' is defined, then
**	it clears that definition to get our default 'main' function back.
*/
#ifdef main
#undef main
#endif

int				main(int argc, char *argv[])
{
	if (debug_init())
		return (ERROR);
	if (config_init())
		return (ERROR);
	if (init_sdl())
		return (ERROR);
	if (init_window())
		return (ERROR);
	if (init_window_display())
		return (ERROR);
	init_scene();
	init_camera(&rt.scene.camera);
	main_check_args();
	if (ui_init())
		return (ERROR);
	if (opencl_init(RT_CL_PLATFORM_UNINITIALIZED))
		return (ERROR);
	return (main_loop());
}
