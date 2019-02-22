/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "libft_char.h"
#include "libft_color.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

static void	rt_output_readfile()
{
	static const char *primitive_types[9] = {
		"N/A",
		"PLANE    ",
		"DISK     ",
		"RECTANGLE",
		"CUBE     ",
		"SPHERE   ",
		"CYLINDER ",
//HUGO
		"INFCYLINDER",
		"CONE     ",
		"OBJ MESH "
	};
	t_object *object;
	unsigned int i;

	debug_output("RT File successfully read:\n");
	debug_output_value("BG Color: #", ft_u32_to_hex(rt.scene.bg_color), TRUE);
	debug_output("Objects:\n");
	i = 0;
	while (i < rt.scene.object_amount)
	{
		object = &rt.scene.objects[i];
		debug_output(primitive_types[(int)object->type]);
		debug_output_value("-> #",	ft_u32_to_hex(object->color), TRUE);
		debug_output_value("NAME: ", (object->name ? object->name : "NULL"), FALSE);
		debug_output_value(" -   pos:",	cl_float3_to_str(&object->pos, 3), TRUE);
		debug_output_value(" -   rot:",	cl_float3_to_str(&object->rot, 3), TRUE);
		debug_output_value(" - scale:",	cl_float3_to_str(&object->scale, 3), TRUE);
		debug_output_value(" - light:",	cl_float3_to_str(&object->light, 3), TRUE);
		++i;
	}
}

static char	*rt_read_object(t_rtparser *p, t_primitive shape)
{
	char		*error;
	t_object	object;

	object.type = shape;
	object.name = NULL;
	object.light = (cl_float3){{ 0., 0., 0. }};
	if ((error = rt_read_arg_color(p, &object.color)) ||
		(error = rt_read_arg_vector(p, &object.pos)) ||
		(error = rt_read_arg_vector(p, &object.rot)) ||
		(error = rt_read_arg_vector(p, &object.scale)))
		return (error);
	if ((error = rt_read_arg_name(p, &object.name)) ||
		(error = rt_read_arg_light(p, &object.light)))
		return (error);
	object.light.x = fmax(0., fmin(object.light.x, 1.));
	object.light.y = fmax(0., fmin(object.light.y, 1.));
	object.light.z = fmax(0., fmin(object.light.z, 1.));
	if (object.light.x + object.light.y + object.light.z > 0.)
		object.material = lightsrc;
	else
		object.material = diffuse;
	object.rgb.x = ft_color_argb32_get_r(object.color) / 255.;
	object.rgb.y = ft_color_argb32_get_g(object.color) / 255.;
	object.rgb.z = ft_color_argb32_get_b(object.color) / 255.;
	rt.scene.objects[p->current_object] = object;
	++(p->current_object);
	return (NULL);
}

static char	*rt_read_command(t_rtparser *p, char *label)
{
	t_primitive	shape;

	shape = none;
	if (ft_strequ(label, "LIGHT"))
		return ("'LIGHT' is not a valid usable 3D object label.\n"
			"To create a light, make any object and add a 'light' argument.");
	else if (ft_strequ(label, "PLANE"))
		shape = plane;
	else if (ft_strequ(label, "DISC") || ft_strequ(label, "DISK"))
		shape = disk;
	else if (ft_strequ(label, "RECTANGLE"))
		shape = rectangle;
	else if (ft_strequ(label, "CUBE"))
		shape = cube;
	else if (ft_strequ(label, "SPHERE"))
		shape = sphere;
	else if (ft_strequ(label, "CYLINDER"))
		shape = cylinder;
//HUGO
	else if (ft_strequ(label, "INFCYLINDER"))
		shape = infcylinder;
	else if (ft_strequ(label, "CONE"))
		shape = cone;
	else if (ft_strequ(label, "OBJ") || ft_strequ(label, "MESH"))
		shape = obj_mesh;
	if (shape)
		return (rt_read_object(p, shape));
	else if (ft_strequ(label, "BG"))
		return (rt_read_arg_color(p, &rt.scene.bg_color));
	else
		return (ft_strjoin("Could not resolve label -> ", label));
}

static char	*rt_read_file(t_rtparser *p)
{
	char	*label;
	char	*error;

	p->line = 1;
	p->index = 0;
	p->current_object = 0;
	while (p->file[p->index])
	{
		rt_read_whitespace(p);
		if (!p->file[p->index])
			break ;
		label = p->file + p->index;
		while (p->file[p->index] &&
			ft_isalpha(p->file[p->index]))
			++(p->index);
		if (!p->file[p->index])
			return ("Unexpected end of file after label");
		p->file[p->index++] = '\0';
		if ((error = rt_read_command(p, label)))
			return (error);
	}
	free(p->file);
	rt.scene.bg_rgb.x = ft_color_argb32_get_r(rt.scene.bg_color) / 255.;
	rt.scene.bg_rgb.y = ft_color_argb32_get_g(rt.scene.bg_color) / 255.;
	rt.scene.bg_rgb.z = ft_color_argb32_get_b(rt.scene.bg_color) / 255.;
	rt.scene.object_amount = p->current_object;
	return (NULL);
}


int			rt_open_file(char *filepath)
{
	int			fd;
	t_rtparser	parser;
	char		*error;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		debug_output_value("Error: Could not open RT file: ", filepath, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	if (ft_readfile(fd, &parser.file))
	{
		debug_output_value("Error: Could not read RT file: ", filepath, FALSE);
		return (ERROR);
	}
	if (close(fd) < 0)
	{
		debug_output_value("Error: Could not close RT file: ", filepath, FALSE);
		debug_output_value("close() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	if ((error = rt_read_file(&parser)))
	{
		debug_output_value("Error: while reading rt file -> at line ",
			ft_s32_to_str(parser.line), TRUE);
		debug_output_error(error, FALSE);
		return (ERROR);
	}
	rt_output_readfile();
	return (OK);
}
