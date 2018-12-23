/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesn <marvin@42.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

/*
**	This here is for windows compatibility, to have the 'main' entry point rather than the native 'WinMain' function for windows GUI programs.
**	Basically, if 'main' is defined we clear that definition, so as to get our default 'main' function back.
*/
#ifdef main
# undef main
#endif

int	main(int argc, char *argv[])
{
	SDL_Window	*window;
	SDL_Surface	*canvas;

	if (argc != 1 || !argv)
		return (ERROR);
	window = NULL;
	canvas = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
		return (ERROR);
	}
	window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_W,
		WINDOW_H,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		return (ERROR);
	}
	canvas = SDL_GetWindowSurface(window);
	SDL_FillRect(canvas, NULL, SDL_MapRGB(canvas->format, 0x88, 0x88, 0x88));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (OK);
}
