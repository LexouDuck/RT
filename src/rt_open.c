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
#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

//TODO Add texture debug output value
void		rt_output_readfile(void)
{
	t_object			*object;
	unsigned int		i;

	debug_output("RT File successfully read:\n");
	debug_output_value("BG Color: #", ft_u32_to_hex(rt.scene.bg_color), TRUE);
	debug_output("Objects:\n");
	i = 0;
	while (i < rt.scene.object_amount)
	{
		object = &rt.scene.objects[i];
		debug_output(rt_get_str_primitive(object->type));
		debug_output("\t-> ");
		debug_output_value("NAME: ", object->name, FALSE);
		debug_output_value("MATERIAL: ", rt_get_str_material(object->material), FALSE);
		debug_output_value("-> #", ft_u32_to_hex(object->color_a), TRUE);
		debug_output_value("-> #", ft_u32_to_hex(object->color_b), TRUE);
		debug_output_value(" - ", cl_float3_to_str(&object->rgb_a, 3), TRUE);
		debug_output_value(" - ", cl_float3_to_str(&object->rgb_b, 3), TRUE);
		debug_output_value(" -   pos:", cl_float3_to_str(&object->pos, 3), TRUE);
		debug_output_value(" -   rot:", cl_float3_to_str(&object->rot, 3), TRUE);
		debug_output_value(" - scale:", cl_float3_to_str(&object->scale, 3), TRUE);
		debug_output_value(" - bbox_vi:", cl_float3_to_str(&object->bbox_os.vi, 3), TRUE);
		debug_output_value(" - bbox_vf:", cl_float3_to_str(&object->bbox_os.vf, 3), TRUE);
		++i;
	}
}

static void	rt_object_init_bbox(t_object *object)
{
	float	render_dist;

	render_dist = rt.scene.render_dist;
	if (object->type == sphere || object->type == cube || object->type == cylinder)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1., -1., -1.}},
			(cl_float3){{1., 1., 1.}}};
	else if (object->type == infcylinder)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1., -render_dist, -1.}},
			(cl_float3){{1., render_dist, 1.}}};
	else if (object->type == paraboloid)
		object->bbox_os = (t_bbox){
			(cl_float3){{-sqrt(render_dist), 0., -sqrt(render_dist)}},
			(cl_float3){{sqrt(render_dist), render_dist, sqrt(render_dist)}}};
	else if (object->type == hyperboloid)
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -render_dist, -render_dist}},
			(cl_float3){{render_dist, render_dist, render_dist}}};
	else if (object->type == cone)
		object->bbox_os = (t_bbox){
			(cl_float3){{-1., 0, -1.}},
			(cl_float3){{1., 1, 1.}}};
	else if (object->type == infcone)
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -render_dist, -render_dist}},
			(cl_float3){{render_dist, render_dist, render_dist}}};
	else
		object->bbox_os = (t_bbox){
			(cl_float3){{-render_dist, -render_dist, -render_dist}},
			(cl_float3){{render_dist, render_dist, render_dist}}};
}

static char	*rt_read_object(t_rtparser *p, t_primitive shape)
{
	char		*error;
	t_object	object;
	t_s32		i;

	object.type = shape;
	object.material = diffuse;
	object.pattern = solid;
	object.uv_projection = planar;
	ft_memclr(&object.name, OBJECT_NAME_MAXLENGTH);
	object.color_a = 0xFFFFFF;
	object.color_b = 0x000000;
	object.rgb_a = (cl_float3){{ 1., 1., 1. }};
	object.rgb_b = (cl_float3){{ 0., 0., 0. }};
	object.pos = (cl_float3){{ 0., 0., 0. }};
	object.rot = (cl_float3){{ 0., 0., 0. }};
	object.scale = (cl_float3){{ 1., 1., 1. }};
	rt_object_init_bbox(&object);
	i = -1;
	while (++i < OBJECT_ARGS_AMOUNT)
	{
		if ((error = rt_read_arg_name(p, (char *)&object.name)) ||
			(error = rt_read_arg_material(p, &object.material, "material")) ||
			(error = rt_read_arg_pattern(p, &object.pattern, "pattern")) ||
			(error = rt_read_arg_projection(p, &object.uv_projection, "projection")) ||
			(error = rt_read_arg_color(p, &object.rgb_a, "color")) ||
			(error = rt_read_arg_color(p, &object.rgb_b, "color2")) ||
			(error = rt_read_arg_vector(p, &object.pos, "pos")) ||
			(error = rt_read_arg_vector(p, &object.rot, "rot")) ||
			(error = rt_read_arg_vector(p, &object.scale, "scale")) ||
			(error = rt_read_arg_vector(p, &object.bbox_os.vi, "bbox_vi")) ||
			(error = rt_read_arg_vector(p, &object.bbox_os.vf, "bbox_vf")) ||
			(error = rt_read_arg_number(p, &object.refrac, "refrac")) ||
			(error = rt_read_arg_number(p, &object.roughness, "roughness")) ||
			(error = rt_read_arg_number(p, &object.opacity, "opacity")))
			return (error);
	}
	update_object(&object);
	rt.scene.objects[p->current_object] = object;
	++(p->current_object);
	return (NULL);
}

static char	*rt_read_command(t_rtparser *p, char *label)
{
	t_primitive	shape;
	char		*error;

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
	else if (ft_strequ(label, "INFCYLINDER"))
		shape = infcylinder;
	else if (ft_strequ(label, "INFCONE"))
		shape = infcone;
	else if (ft_strequ(label, "CONE"))
		shape = cone;
	else if (ft_strequ(label, "PARABOLOID"))
		shape = paraboloid;
	else if (ft_strequ(label, "HYPERBOLOID"))
		shape = hyperboloid;
	else if (ft_strequ(label, "OBJ") || ft_strequ(label, "MESH"))
		shape = obj_mesh;
	if (shape)
		return (p->current_object < OBJECT_MAX_AMOUNT ? rt_read_object(p, shape)
			: "Import error: Maximum object amount limit has been reached.");
	else if (ft_strequ(label, "BG"))
	{
		error = rt_read_arg_color(p, &rt.scene.bg_rgb, "color");
		update_scene();
		return (error);
	}
	else
		return (ft_strjoin("Could not resolve label -> ", label));
}

char		*rt_read_file(t_rtparser *p)
{
	char	*label;
	char	*error;

	p->line = 1;
	p->index = 0;
	p->current_object = rt.scene.object_amount;
	while (p->file[p->index])
	{
		rt_read_whitespace(p);
		if (!p->file[p->index])
			break ;
		label = p->file + p->index;
		while (p->file[p->index] && ft_isalpha(p->file[p->index]))
			++(p->index);
		if (!p->file[p->index])
			return ("Unexpected end of file after label");
		p->file[p->index++] = '\0';
		if ((error = rt_read_command(p, label)))
			return (error);
	}
	rt.scene.bg_rgb.x = ft_color_argb32_get_r(rt.scene.bg_color) / 255.;
	rt.scene.bg_rgb.y = ft_color_argb32_get_g(rt.scene.bg_color) / 255.;
	rt.scene.bg_rgb.z = ft_color_argb32_get_b(rt.scene.bg_color) / 255.;
	rt.scene.object_amount = p->current_object;
	return (NULL);
}

int			rt_open_file(char *filepath, t_rtparser *p)
{
	int			fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		debug_output_value("Error: Could not open RT file: ", filepath, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	if (ft_readfile(fd, &p->file))
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
	return (OK);
}
