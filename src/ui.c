/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 15:34:04 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"
#include "libft_memory.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

/*
**	Set the current palette for the UI tileset
*/

SDL_Palette		*ui_set_palette(SDL_Surface *surface, t_u32 const *palette)
{
	SDL_Color	result[PALETTE];
	t_u8		i;

	if (surface == NULL || surface->format == NULL ||
		palette == NULL || surface->format->palette == NULL)
	{
		debug_output_error(
			"Error during palette switching: Null argument given", FALSE);
		return (NULL);
	}
	i = 0;
	while (i < PALETTE)
	{
		result[i].a = 0xFF;
		result[i].r = ft_color_argb32_get_r(palette[i]);
		result[i].g = ft_color_argb32_get_g(palette[i]);
		result[i].b = ft_color_argb32_get_b(palette[i]);
		++i;
	}
	if (SDL_SetPaletteColors(surface->format->palette, result, 0, PALETTE))
	{
		debug_output_error("Error during palette switching:", TRUE);
		return (NULL);
	}
	return (surface->format->palette);
}

void			ui_set_result_pixels(t_u8 const *chr, t_u16 tile,
				t_u8 **result_pixels)
{
	t_u16			index;
	t_u8			pixel;
	t_u8			x;
	t_u8			y;

	x = -1;
	y = -1;
	index = (tile / TILESET_W_TILES) * TILE * TILESET_W
	+ (tile % TILESET_W_TILES) * TILE;
	while (++y < TILE)
	{
		while (++x < TILE)
		{
			pixel = 0;
			pixel |= 1 & (chr[tile * CHR_BYTES_PER_TILE + 8 + y] >> (7 - x));
			pixel <<= 1;
			pixel |= 1 & (chr[tile * CHR_BYTES_PER_TILE + 0 + y] >> (7 - x));
			(*result_pixels)[index + x] = pixel;
		}
		index += TILESET_W;
		x = -1;
	}
	return ;
}

/*
**	Creates an 8bpp indexed SDL_Surface from 2bpp
** NES-compliant pixel data ('.chr' files)
**	- chr:	The chr file -> an array of 8x8 tiled pixel data
*/

SDL_Surface		*ui_set_tileset(t_u8 const *chr, size_t length)
{
	SDL_Surface		*result;
	t_u8			*result_pixels;
	t_u16			tile;
	t_u16			tilecount;

	result = NULL;
	tilecount = length / CHR_BYTES_PER_TILE;
	tile = -1;
	if (!chr)
		return (NULL);
	if (!(result_pixels = (t_u8*)ft_memalloc(length * 4)))
		return (NULL);
	while (++tile < tilecount)
		ui_set_result_pixels(chr, tile, &result_pixels);
	if (!(result = SDL_CreateRGBSurfaceWithFormatFrom(result_pixels, TILESET_W,
		((tilecount / TILESET_W_TILES) + (tilecount % TILESET_W_TILES ? 1 : 0))
		* TILE, 8, TILESET_W, SDL_PIXELFORMAT_INDEX8)))
	{
		debug_output_error("Could not create SDL_Surface: ", TRUE);
		free(result_pixels);
		return (NULL);
	}
	SDL_SetSurfaceBlendMode(result, SDL_BLENDMODE_NONE);
	return (result);
}
