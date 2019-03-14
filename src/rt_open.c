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

#include "libft_char.h"
#include "libft_color.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"

static char	*rt_read_object(t_rtparser *p, t_primitive shape)
{
	char		*error;
	t_object	object;
	t_s32		i;

	object.type = shape;
	init_object(&object);
	i = 0;
	while (++i < OBJECT_ARGS_AMOUNT)
	{
		if ((error = rt_read_object_arg(p, &object)))
			return (error);
		++i;
	}
	update_object(&object);
	g_rt.scene.objects[p->current_object] = object;
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
	else if (ft_strequ(label, "OBJ") || ft_strequ(label, "MESH"))
		shape = obj_mesh;
	else
		rt_read_getprimitive(label, &shape);
	if (shape)
		return (p->current_object < OBJECT_MAX_AMOUNT ? rt_read_object(p, shape)
			: "Import error: Maximum object amount limit has been reached.");
	else if (ft_strequ(label, "BG"))
	{
		error = rt_read_arg_color(p, &g_rt.scene.bg_rgb, "color");
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
	p->current_object = g_rt.scene.object_amount;
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
	g_rt.scene.bg_rgb.x = ft_color_argb32_get_r(g_rt.scene.bg_color) / 255.;
	g_rt.scene.bg_rgb.y = ft_color_argb32_get_g(g_rt.scene.bg_color) / 255.;
	g_rt.scene.bg_rgb.z = ft_color_argb32_get_b(g_rt.scene.bg_color) / 255.;
	g_rt.scene.object_amount = p->current_object;
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
	if (ft_readfile(fd, &p->file, 0xFFFF))
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
