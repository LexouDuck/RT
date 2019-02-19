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

static void	update_window()
{
	SDL_Rect	dest;

	// Fill the window pixel buffer with black
	if (SDL_FillRect(rt.sdl.window_surface, NULL, 0x000000))
		debug_output_error(
			"Error during update_window() -> Screen clear: ", TRUE);

	// display the UI
	ui_render_objects();
	ui_render_menubar();
	if (rt.ui.menubar.selection != -1)
		ui_render_dropdown(&rt.ui.dropdowns[rt.ui.menubar.selection]);

	// Do the 3d render if needed
	if (rt.must_render)
		render();
	dest = rt.sdl.window_surface->clip_rect;
	dest.x += UI_WIDTH;
	dest.w -= UI_WIDTH;
	if (SDL_BlitSurface(rt.canvas, &rt.canvas->clip_rect, rt.sdl.window_surface, &dest))
		debug_output_error("Error during update_window() -> render blit: ", TRUE);

	ui_render_caminfo(&rt.scene.camera);

	// and update the window display
	if (SDL_UpdateTexture(rt.sdl.window_texture, NULL,
		rt.sdl.window_surface->pixels, rt.sdl.window_surface->pitch))
		debug_output_error("Error during window update: ", TRUE);
//	if (SDL_RenderClear(rt.sdl.window_renderer))
//		debug_output_error("Error during render screen clear: ", TRUE);
	if (SDL_RenderCopy(rt.sdl.window_renderer, rt.sdl.window_texture, NULL, NULL))
		debug_output_error("Error during render copy: ", TRUE);
	SDL_RenderPresent(rt.sdl.window_renderer);
	rt.must_render = FALSE;
}

/*
**	The main program loop: pretty much everything is called from here
**	Runs at 60fps (the 3 first lines of code inside the loop do this)
*/
static int	main_loop()
{
	t_bool			loop = TRUE;
	t_u32			frame_wait = 0;

	rt.sdl.current_frame = 0;
	rt.must_render = TRUE;
	while (loop)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), frame_wait))
			SDL_Delay(1);
		frame_wait = SDL_GetTicks() + FRAME_MS;
		++rt.sdl.current_frame;
		loop = event_checkevents(rt.sdl.window);

		// TODO do stuff here

		update_window();
	}
	config_save();
	config_free();
	for (int i = 0; i < RT_CL_KERNEL_AMOUNT; ++i)
		clReleaseKernel(rt.ocl.kernels[i]);
	clReleaseCommandQueue(rt.ocl.cmd_queue);
	clReleaseProgram(rt.ocl.program);
	clReleaseContext(rt.ocl.context);
	SDL_DestroyWindow(rt.sdl.window);
	SDL_Quit();
	return (OK);
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

int			main(int argc, char* argv[])
{
//printf("debug: init debug\n");
	if (debug_init())
		return (ERROR);
//printf("debug: init config\n");
	if (config_init())
		return (ERROR);
//printf("debug: init sdl\n");
	if (init_sdl())
		return (ERROR);
//printf("debug: init window\n");
	if (init_window())
		return (ERROR);
	if (init_window_display())
		return (ERROR);

	init_scene();
	init_camera(&rt.scene.camera);

	if (argc > 1)
	{
		int i = 1;
		ui_menu_file_open(argv[i]);
		while (++i < argc)
			ui_menu_file_import(argv[i]);
	}

//printf("debug: init ui\n");
	if (ui_init())
		return (ERROR);
//printf("debug: init opencl\n");
	if (opencl_init())
		return (ERROR);
	return (main_loop());
}
