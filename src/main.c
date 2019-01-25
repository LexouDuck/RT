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

#include "../rt.h"
#include "config.h"
#include "debug.h"

/*
**	The main program loop: pretty much everything is called from here
*/
static int	main_loop(
	SDL_Window*	window,
	SDL_Texture* screen,
	SDL_Renderer* renderer)
{
	t_bool			loop = TRUE;
	t_u32			frame_wait = 0;

	while (loop)
	{
		// wait for 60fps frameroll (1000ms / 60 = 16ms)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), frame_wait))
			SDL_Delay(1);
		frame_wait = SDL_GetTicks() + FRAME_MS;

		loop = event_checkevents(window);

		// TODO do stuff here

		render(screen, renderer);
	}
	config_save();
	config_free();
	SDL_DestroyWindow(window);
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
	SDL_Window*	window;
	SDL_Texture* screen;
	SDL_Renderer* renderer;

	if (argc != 1 || !argv)
		return (ERROR);

	if (debug_init())
		return (ERROR);
	config_init();

	if (init_sdl())
		return (ERROR);
	if (init_window(&window))
		return (ERROR);
	if (init_screen(window, &screen, &renderer))
		return (ERROR);

	render_init();

	return (main_loop(window, screen, renderer));
}
