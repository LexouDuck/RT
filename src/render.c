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
#include "debug.h"

#include "libft_memory.h"

void	render_init()
{

}

void	render(SDL_Texture* screen, SDL_Renderer* renderer)
{
	// fill the screen->pixels buffer here

	// and update the window display
	if (SDL_RenderClear(renderer))
		debug_output_error("Error during render screen clear: ", TRUE);
	if (SDL_RenderCopy(renderer, screen, NULL, NULL))
		debug_output_error("Error during render copy: ", TRUE);
	SDL_RenderPresent(renderer);
}
