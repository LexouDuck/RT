/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

static void		write_float(int fd, cl_float value, char *label)
{
	char *tmp;

	if ((tmp = ft_f32_to_str(value, 5)))
	{
		ft_write_str(fd, label);
		ft_write_line(fd, tmp);
		free(tmp);
	}
	return ;
}

static void		write_float3(int fd, cl_float3 *vector, char *label)
{
	char *tmp;

	if ((tmp = cl_float3_to_str(vector, 5)))
	{
		ft_write_str(fd, label);
		ft_write_line(fd, tmp);
		free(tmp);
	}
	return ;
}

/*
** this function write revery data of the map and call above function.
*/

static void		write_enums(int fd, t_object *object)
{
	char *tmp;

	if ((tmp = rt_get_str_primitive(object->type)))
		ft_write_line(fd, tmp);
	if (ft_strlen(object->name))
	{
		ft_write_char(fd, '"');
		ft_write_str(fd, object->name);
		ft_write_line(fd, "\"");
	}
	tmp = rt_get_str_material(object->material);
	ft_write_str(fd, "material:");
	ft_write_line(fd, tmp);
	tmp = rt_get_str_pattern(object->pattern);
	ft_write_str(fd, "pattern:");
	ft_write_line(fd, tmp);
	tmp = rt_get_str_projection(object->uvw_projection);
	ft_write_str(fd, "projection:");
	ft_write_line(fd, tmp);
	tmp = rt_get_str_bump(object->bump_type);
	ft_write_str(fd, "bump:");
	ft_write_line(fd, tmp);
}

/*
** this function print Back ground color on the savefile
*/

static void		write_bg_color(int fd)
{
	char *tmp;

	if ((tmp = ft_u32_to_hex(g_rt.scene.bg_color)))
	{
		ft_write_str(fd, "BG #");
		ft_write_line(fd, tmp);
		ft_write_char(fd, '\n');
		free(tmp);
	}
	return ;
}

/*
** this function write a map and save in a new file or in the same file.
*/

void			rt_save(int fd)
{
	t_s32		i;
	t_object	*object;

	write_bg_color(fd);
	i = -1;
	while (++i < (t_s32)g_rt.scene.object_amount)
	{
		object = &g_rt.scene.objects[i];
		write_enums(fd, object);
		write_float3(fd, &object->rgb_a, "color:");
		write_float3(fd, &object->rgb_b, "color2:");
		write_float3(fd, &object->pos, "pos:");
		write_float3(fd, &object->rot, "rot:");
		write_float3(fd, &object->scale, "scale:");
		write_float3(fd, &object->bbox_os.vi, "bbox_vi:");
		write_float3(fd, &object->bbox_os.vf, "bbox_vf:");
		write_float3(fd, &object->uvw_scale, "uvw_scale:");
		write_float3(fd, &object->uvw_offset, "uvw_offset:");
		write_float(fd, object->refrac, "refrac:");
		write_float(fd, object->roughness, "roughness:");
		write_float(fd, object->opacity, "opacity:");
		ft_write_char(fd, '\n');
	}
	return ;
}
