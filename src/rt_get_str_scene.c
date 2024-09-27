/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "rt_scene.h"

inline char		*rt_get_str_rendermode(t_rendermode rendermode)
{
	static char	*rendermodes[RENDER_MODES] = {
		"MONTE-CARLO",
		"OBJECT BBOX",
		"WORLD  BBOX",
		"SOLID COLOR",
		"SLD TEXTURE",
		"NORMALS MAP"
	};

	return (rendermodes[rendermode]);
}

inline char		*rt_get_str_cameramodel(t_camera_model cameramodel)
{
	static char	*cameramodels[CAMERA_MODELS] = {
		"PINHOLE",
		"BLUR SIMPLE",
		"BLUR FOCAL",
		"AUTO FOCUS",
		"ORTHOGRAPHIC"
	};

	return (cameramodels[cameramodel]);
}
