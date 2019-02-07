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

#include "../assets.h"
#include "../rt.h"
#include "config.h"
#include "debug.h"
#include "ui.h"
#include "libft_convert.h" //Tristan@Alexis : TODO remove if unnecessary ?

static void	update_window()
{
	if (SDL_FillRect(rt.sdl.window_surface, NULL, 0x000000))
		debug_output_error(
			"Error during update_window() -> Screen clear: ", TRUE);
	// display the UI
	render_ui_menubar();
	if (rt.ui.menubar.selection != -1)
		render_ui_dropdown(&rt.ui.dropdowns[rt.ui.menubar.selection]);

	// Do the 3d render if needed
	if (rt.must_render)
		render();
	if (rt.canvas && SDL_BlitSurface(rt.canvas, NULL, rt.sdl.window_surface, NULL))
		debug_output_error(
			"Error during update_window() -> render blit: ", TRUE);

	// and update the window display
	if (SDL_UpdateTexture(rt.sdl.window_texture, NULL,
		rt.sdl.window_surface->pixels, rt.sdl.window_surface->pitch))
		debug_output_error("Error during window update: ", TRUE);
	if (SDL_RenderClear(rt.sdl.window_renderer))
		debug_output_error("Error during render screen clear: ", TRUE);
	if (SDL_RenderCopy(rt.sdl.window_renderer, rt.sdl.window_texture, NULL, NULL))
		debug_output_error("Error during render copy: ", TRUE);
	SDL_RenderPresent(rt.sdl.window_renderer);
}

/*
**	The main program loop: pretty much everything is called from here
**	Runs at 60fps (the 3 first lines of code inside the loop do this)
*/
static int	main_loop()
{
	t_bool			loop = TRUE;
	t_u32			frame_wait = 0;

	while (loop)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), frame_wait))
			SDL_Delay(1);
		frame_wait = SDL_GetTicks() + FRAME_MS;

		loop = event_checkevents(rt.sdl.window);
		rt.mouse_button = SDL_GetMouseState(&rt.mouse.x, &rt.mouse.y);

		// TODO do stuff here

		update_window();
	}
	config_save();
	config_free();
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
	// TODO open files given as args
	if (argc != 1 || !argv)
		return (ERROR);

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
	if (ui_init())
		return (ERROR);
	if (init_opencl())
		return (ERROR);
	if (render_init())
		return (ERROR);
	return (main_loop());
}
