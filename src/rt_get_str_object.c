/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_str_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "rt_scene.h"

inline char		*rt_get_str_primitive(t_primitive primitive)
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
		"PARABOLOID",
		"HYPERBOLOID",
		"INFCYLINDER",
		"INFCONE",
		"SADDLE",
		"OBJ MESH",
	};

	return (primitives[primitive]);
}

inline char		*rt_get_str_material(t_material material)
{
	static char	*materials[MATERIALS] = {
		"LIGHT",
		"DIFFUSE",
		"TRANSPARENT",
		"SPECULAR",
	};

	return (materials[material]);
}

inline char		*rt_get_str_pattern(t_pattern pattern)
{
	static char	*patterns[TEXTURE_PATTERNS] = {
		"SOLID",
		"H_WAVES",
		"V_WAVES",
		"D_WAVES",
		"H_STRIPES",
		"V_STRIPES",
		"CHECKER",
		"IMAGE",
		"PERLIN",
		"MARBLE",
		"WOOD",
	};

	return (patterns[pattern]);
}

inline char		*rt_get_str_projection(t_projection projection)
{
	static char	*projections[TEXTURE_PROJECTIONS] = {
		"SPHERICAL",
		"CUBIC",
		"CYLINDRICAL",
	};

	return (projections[projection]);
}

inline char		*rt_get_str_bump(t_bump bump_type)
{
	static char	*bump_types[BUMP_TYPES] = {
		"FLAT",
		"BUMP",
	};

	return (bump_types[bump_type]);
}
