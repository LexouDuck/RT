/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesn <marvin@42.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2018/11/06 16:53:30 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "SDL2-2.0.9/include/SDL.h"
# include "libft/libft.h"

# define WINDOW_W	640
# define WINDOW_H	480
# define WINDOW_TITLE	"RT: 42 Raytracer"

/*
** === CAMERA MODES ===
*/
# define CAMERA_NONE		0
# define CAMERA_ROTATE		1
# define CAMERA_ZOOM		2
# define CAMERA_PAN			3

#endif
