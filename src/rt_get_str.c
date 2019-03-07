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

inline char *rt_get_str_primitive(t_primitive primitive)
{
	static char	*primitives[PRIMITIVES] = {
		"N/A",
		"SPHERE",
		"CUBE",
		"CYLINDER",
		"CONE",
		"PLANE",
		"RECTANGLE",
		"DISK",
		"TRIANGLE",
		"SADDLE",
		"PARABOLOID",
		"HYPERBOLOID",
		"INFCYLINDER",
		"INFCONE",
		"OBJ MESH",
	};

	return (primitives[primitive]);
}

inline char *rt_get_str_material(t_material material)
{
	static char	*materials[MATERIALS] = {
		"LIGHT",
		"DIFFUSE",
		"TRANSPARENT",
		"SPECULAR",
	};

	return (materials[material]);
}

inline char	*rt_get_str_rendermode(t_rendermode rendermode)
{
	static char	*rendermodes[RENDER_MODES] = {
		"MONTE-CARLO",
		"OBJECT BBOX",
		"WORLD  BBOX",
		"SOLID COLOR",
		"SLD TEXTURE"
	};

	return (rendermodes[rendermode]);
}

inline char	*rt_get_str_cameramodel(t_camera_model cameramodel)
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

inline char	*rt_get_str_pattern(t_pattern pattern)
{
	static char	*patterns[TEXTURE_PATTERNS] = {
		"SOLID",
		"H_WAVES",
		"V_WAVES",
		"D_WAVES",
		"H_STRIPES",
		"V_STRIPES",
		"CHECKER",
		"HUE",
		"PERLIN",
		"MARBLE",
		"WOOD",
	};

	return (patterns[pattern]);
}


inline char	*rt_get_str_projection(t_uv_projection projection)
{
	static char	*projections[TEXTURE_PROJECTIONS] = {
		"SPHERICAL",
		"CUBIC",
		"CYLINDRICAL",
	};

	return (projections[projection]);
}
