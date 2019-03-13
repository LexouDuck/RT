/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_img_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:04:26 by hbruvry           #+#    #+#             */
/*   Updated: 2019/03/11 15:05:28 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_color.h"
#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

void		rt_fill_image_texture(cl_uint **img_texture,
			Uint32 *img_pixels, SDL_PixelFormat *format)
{
	Uint32	pixel;
	Uint32	tmp;
	int		x;
	int		y;

	x = -1;
	y = -1;
	while (++y < 100)
	{
		while (++x < 100)
		{
			pixel = img_pixels[(y * 100) + x];
			tmp = (pixel & format->Rmask) >> format->Rshift;
			tmp = tmp << format->Rloss;
			(*img_texture)[(y * 100) + x] = (cl_uint)tmp * 0x10000;
			tmp = (pixel & format->Gmask) >> format->Gshift;
			tmp = tmp << format->Gloss;
			(*img_texture)[(y * 100) + x] += (cl_uint)tmp * 0x100;
			tmp = (pixel & format->Bmask) >> format->Bshift;
			tmp = tmp << format->Bloss;
			(*img_texture)[(y * 100) + x] += (cl_uint)tmp * 0x1;
		}
		x = -1;
	}
	return ;
}

/*
** Uint32			pixel;
** Uint32			tmp;
** int				x;
** int				y;
*/

void		rt_get_img_texture(cl_uint **img_texture)
{
	SDL_Surface		*surface;
	SDL_PixelFormat	*format;
	Uint32			*img_pixels;

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
	rt_fill_image_texture(img_texture, img_pixels, format);
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
	return ;
}
