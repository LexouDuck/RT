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
	static char	*primitives[] = {
		"N/A",
		"SPHERE     ",
		"CUBE       ",
		"CYLINDER   ",
		"CONE       ",
		"PLANE      ",
		"RECTANGLE  ",
		"DISK       ",
		"OBJ MESH   ",
		"PARABOLOID ",
		"HYPERBOLOID",
		"SADDLE     ",
		"INFCYLINDER",
		"INFCONE    ",
	};

	return (primitives[primitive]);
}

inline char *rt_get_str_material(t_material material)
{
	static char	*materials[] = {
		"LIGHT      ",
		"DIFFUSE    ",
		"TRANSPARENT",
		"SPECULAR   ",
	};

	return (materials[material]);
}