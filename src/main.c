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

static void		main_exit(void)
{
	if (g_rt.ui.current_textinput.input)
	{
		free(g_rt.ui.current_textinput.input);
		g_rt.ui.current_textinput.input = NULL;
	}
	config_save();
	config_free();
	opencl_freeall();
	SDL_DestroyWindow(g_rt.sdl.window);
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
	g_rt.sdl.current_frame = 0;
	g_rt.must_render = TRUE;
	g_rt.sdl.loop = TRUE;
	while (g_rt.sdl.loop)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), frame_wait))
			SDL_Delay(1);
		frame_wait = SDL_GetTicks() + FRAME_MS;
		++g_rt.sdl.current_frame;
		event_checkevents();
		update_window();
	}
	debug_output("Attempting to close program...\n");
	main_exit();
	debug_output("Program closed successfully.\n");
	return (OK);
}

static void		main_check_args(int argc, char *argv[])
{
	int	i;

	if (argc > 1)
	{
		i = 1;
		g_rt.filepath = argv[i];
		rt_file_open(g_rt.filepath);
		while (++i < argc)
		{
			g_rt.filepath = NULL;
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
# undef main
#endif

int				main(int argc, char *argv[])
{
	debug_perror("init debug & config");
	if (debug_init())
		return (ERROR);
	if (config_init())
		return (ERROR);
	debug_perror("init SDL & window");
	if (init_sdl())
		return (ERROR);
	if (init_window())
		return (ERROR);
	debug_perror("init display");
	if (init_window_display())
		return (ERROR);
	init_scene();
	init_camera(&g_rt.scene.camera);
	rt_get_img_texture(&g_rt.img_texture);
	main_check_args(argc, argv);
	debug_perror("init UI");
	if (ui_init())
		return (ERROR);
	debug_perror("init OpenCL");
	if (opencl_init(RT_CL_PLATFORM_UNINITIALIZED))
		return (ERROR);
	return (main_loop());
}
