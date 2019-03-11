/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_create_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 15:03:29 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_color.h"
#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

/*
static t_float3	rt_get_texture_pixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	return (p[0] | p[1] << 8 | p[2] << 16);
}
*/

void		rt_get_img_texture(cl_uint **img_texture)
{
	SDL_Surface		*surface;
	SDL_PixelFormat	*format;
	Uint32			*img_pixels;
	Uint32			pixel;
	Uint32			tmp;
	int				x;
	int				y;

	if (!(surface = SDL_LoadBMP("img_texture.bmp")))
	{
		debug_output_error("Texture BMP image file could not be loaded.", TRUE);
		return ;
	}
	SDL_LockSurface(surface);
	format = surface->format;
	img_pixels = (Uint32*)(surface->pixels);
	if (!(*img_texture = (cl_uint*)malloc(sizeof(cl_uint) * (100 * 100))))
	{
		SDL_FreeSurface(surface);
		return ;
	}
	x = -1;
	y = -1;
	while (++y < 100)
	{
		while (++x < 100)
		{
			pixel = img_pixels[(y * 100) + x];
			tmp = pixel & format->Rmask;
			tmp = tmp >> format->Rshift;
			tmp = tmp << format->Rloss;
			(*img_texture)[(y * 100) + x] = (cl_uint)tmp * 0x10000;
			tmp = pixel & format->Gmask;
			tmp = tmp >> format->Gshift;
			tmp = tmp << format->Gloss;
			(*img_texture)[(y * 100) + x] += (cl_uint)tmp * 0x100;
			tmp = pixel & format->Bmask;
			tmp = tmp >> format->Bshift;
			tmp = tmp << format->Bloss;
			(*img_texture)[(y * 100) + x] += (cl_uint)tmp * 0x1;
		}
		x = -1;
	}
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
	return ;
}