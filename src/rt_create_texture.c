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

void		rt_create_rgb_texture(cl_float3 **rgb_texture)
{
	SDL_Surface		*surface;
	SDL_PixelFormat	*format;
	Uint32			*img_pixels;
	Uint32			pixel;
	Uint32			tmp;
	int				x;
	int				y;
	int				h_inc;
	int				w_inc;

	if (!(surface = SDL_LoadBMP("img_texture.bmp")))
	{
		debug_output_error("Texture BMP image file could not be loaded.", TRUE);
		return ;
	}
	SDL_LockSurface(surface);
	format = surface->format;
	img_pixels = (Uint32*)(surface->pixels);
	h_inc = (int)(surface->h / 100);
	w_inc = (int)(surface->w / 100);
	if (!(*rgb_texture = (cl_float3*)malloc(sizeof(cl_float3) * (100 * 100))))
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
			pixel = img_pixels[(y * h_inc * surface->w) + (x * w_inc)];
			tmp = pixel & format->Rmask;
			tmp = tmp >> format->Rshift;
			tmp = tmp << format->Rloss;
			(*rgb_texture)[y * 100 + x].x = (cl_float)tmp / 255.;
			tmp = pixel & format->Gmask;
			tmp = tmp >> format->Gshift;
			tmp = tmp << format->Gloss;
			(*rgb_texture)[y * 100 + x].y = (cl_float)tmp / 255.;
			tmp = pixel & format->Bmask;
			tmp = tmp >> format->Bshift;
			tmp = tmp << format->Bloss;
			(*rgb_texture)[y * 100 + x].z = (cl_float)tmp / 255.;
	//		debug_output_value("rgb :", cl_float3_to_str(&(*rgb_texture)[y * 100 + x], 3), TRUE);
		}
		x = -1;
	}
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
	return ;
}