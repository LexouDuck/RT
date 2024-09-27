/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_open_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_string.h"

#include "../rt.h"

void		rt_read_whitespace(t_rtparser *p)
{
	char	*file;

	file = p->file;
	while (file[p->index] &&
		(ft_isspace(file[p->index]) || file[p->index] == '/'))
	{
		if (file[p->index] == '\n')
			++(p->line);
		else if (file[p->index] == '/')
		{
			if (file[p->index + 1] == '/')
			{
				while (file[p->index] && file[p->index] != '\n')
					++(p->index);
				++(p->line);
			}
			else
				break ;
		}
		++(p->index);
	}
}

char		*rt_read_error(char expected, char *description, char instead)
{
	char	*result;
	size_t	length;
	size_t	i;

	length = ft_strlen(description);
	if (!(result = (char*)malloc((64 + length) * sizeof(char))))
		return (NULL);
	i = 0;
	ft_strcpy(result, "Expected \'");
	i += 10;
	result[i++] = expected;
	ft_strcpy(result + i, "\' (");
	i += 3;
	ft_strcpy(result + i, description);
	i += length;
	ft_strcpy(result + i, "), but instead found: \'");
	i += 21;
	result[i++] = instead;
	return (result);
}

char		*rt_read_object_arg(t_rtparser *p, t_object *object)
{
	char		*error;

	if ((error = rt_read_arg_name(p, (char *)&object->name)) ||
		(error = rt_read_arg_material(p, &object->material, "material")) ||
		(error = rt_read_arg_pattern(p, &object->pattern, "pattern")) ||
		(error = rt_read_arg_projection(p, &object->uvw_projection,
			"projection")) ||
		(error = rt_read_arg_bump(p, &object->bump_type, "bump")) ||
		(error = rt_read_arg_color(p, &object->rgb_a, "color")) ||
		(error = rt_read_arg_color(p, &object->rgb_b, "color2")) ||
		(error = rt_read_arg_vector(p, &object->pos, "pos")) ||
		(error = rt_read_arg_vector(p, &object->rot, "rot")) ||
		(error = rt_read_arg_vector(p, &object->scale, "scale")) ||
		(error = rt_read_arg_vector(p, &object->bbox_os.vi, "bbox_vi")) ||
		(error = rt_read_arg_vector(p, &object->bbox_os.vf, "bbox_vf")) ||
		(error = rt_read_arg_vector(p, &object->uvw_scale, "uvw_scale")) ||
		(error = rt_read_arg_vector(p, &object->uvw_offset, "uvw_offset")) ||
		(error = rt_read_arg_number(p, &object->refrac, "refrac")) ||
		(error = rt_read_arg_number(p, &object->roughness, "roughness")) ||
		(error = rt_read_arg_number(p, &object->opacity, "opacity")))
		return (error);
	return (NULL);
}

void		rt_read_getprimitive(char const *label, t_primitive *shape)
{
	if (ft_strequ(label, "PLANE"))
		*shape = plane;
	else if (ft_strequ(label, "DISC") || ft_strequ(label, "DISK"))
		*shape = disk;
	else if (ft_strequ(label, "RECTANGLE"))
		*shape = rectangle;
	else if (ft_strequ(label, "TRIANGLE"))
		*shape = triangle;
	else if (ft_strequ(label, "CUBE"))
		*shape = cube;
	else if (ft_strequ(label, "SPHERE"))
		*shape = sphere;
	else if (ft_strequ(label, "CYLINDER"))
		*shape = cylinder;
	else if (ft_strequ(label, "INFCYLINDER"))
		*shape = infcylinder;
	else if (ft_strequ(label, "INFCONE"))
		*shape = infcone;
	else if (ft_strequ(label, "CONE"))
		*shape = cone;
	else if (ft_strequ(label, "PARABOLOID"))
		*shape = paraboloid;
	else if (ft_strequ(label, "HYPERBOLOID"))
		*shape = hyperboloid;
}
