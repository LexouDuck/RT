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
#include "libft_color.h"
#include "libft_convert.h"

#include "../rt.h"

void		rt_get_arg_color_rgb(char c, t_rtparser *p, cl_float3 *result)
{
	char	*str;
	t_u32	color;

	++(p->index);
	str = p->file + p->index;
	while ((c = p->file[p->index]) && (ft_isdigit(c) ||
		('A' <= c && c <= 'F') || ('a' <= c && c <= 'f')))
		++(p->index);
	if (p->file[p->index] == '\n')
		p->line += 1;
	p->file[p->index] = '\0';
	++(p->index);
	color = ft_hex_to_u32(str);
	result->x = ft_color_argb32_get_r(color) / 255.;
	result->y = ft_color_argb32_get_g(color) / 255.;
	result->z = ft_color_argb32_get_b(color) / 255.;
	return ;
}

char		*rt_read_arg_color(t_rtparser *p, cl_float3 *result,
			char const *label)
{
	char	c;
	char	*str;

	rt_read_whitespace(p);
	if ((c = p->file[p->index]) == '\0')
		return (NULL);
	else if (c == '#')
	{
		rt_get_arg_color_rgb(c, p, result);
		return (NULL);
	}
	else
	{
		str = rt_read_arg_vector(p, result, label);
		(result->x < 0.) ? result->x = 0. : 0;
		(result->x > 1.) ? result->x = 1. : 0;
		(result->y < 0.) ? result->y = 0. : 0;
		(result->y > 1.) ? result->y = 1. : 0;
		(result->z < 0.) ? result->z = 0. : 0;
		(result->z > 1.) ? result->z = 1. : 0;
		return (str);
	}
}

t_bool		rt_check_arg_material_label(t_rtparser *p, t_material *result)
{
	char const	*str;
	size_t		length;
	size_t		i;

	i = 0;
	while (i < MATERIALS)
	{
		str = rt_get_str_material((t_material)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_material)i;
			p->index += length;
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

char		*rt_read_arg_material(t_rtparser *p, t_material *result,
			char const *label)
{
	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index,
	label, ft_strlen(label)))
	{
		return (NULL);
	}
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
	{
		return (rt_read_error(':', "without spaces before material string",
		p->file[p->index]));
	}
	++(p->index);
	if (rt_check_arg_material_label(p, result))
		return (NULL);
	return ("No valid material enum label encountered");
}
