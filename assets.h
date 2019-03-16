/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASSETS_H
# define __ASSETS_H

# include "libft.h"

# define TILE	8
# define PALETTE	4

/*
**	This header holds all the external files to be embedded within the program.
**	These binary files are compiled with 'ld' (with the '-b binary' option),
**	and they are then linked within the program executable with 'gcc'.
*/

/*
**	- CHR	-> NES 8x8 Tiled Pixel Data Format
**	Stores 256 distinct 'tiles' (or 'chars', hence chr) of 8x8 pixel data.
**	These pixels are 2-bits (can be 0-3), so as to go with a 4-color palette.
*/
# define CHR_SIZE	4096

/*
**	2bpp = 16 bytes of memory per 8x8 tile
*/
# define CHR_BYTES_PER_TILE		16
# define TILESET_W_TILES		16
# define TILESET_W		(TILESET_W_TILES * TILE)

/*
**	UI Tileset: 4-color 2bpp CHR pixel data format
*/
# ifdef __APPLE__
#  define OS_ASSETS	0

	extern const t_u8 binary___inc_ui_chr_start[1];
	extern const t_u8 _binary___inc_ui_chr_start[1];

# else
#  ifdef __WIN32__
#   define OS_ASSETS	1
#  else
#   define OS_ASSETS	2
#  endif

	extern const t_u8 binary___inc_ui_chr_start[CHR_SIZE];
	extern const t_u8 _binary___inc_ui_chr_start[CHR_SIZE];
	void	*getsectiondata(void *ptr,
		char const *section,
		char const *segment,
		size_t *size);

# endif

#endif
