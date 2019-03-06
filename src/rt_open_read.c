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

char		*rt_read_arg_name(t_rtparser *p, char *result)
{
	t_bool	has_arg;
	char	symbol;
	size_t	offset;

	rt_read_whitespace(p);
	if (!p->file[p->index])
		return (NULL);
	if ((has_arg = ft_strnequ(p->file + p->index, "name:", 5)))
		p->index += 5;
	symbol = p->file[p->index];
	if (symbol != '\"' && symbol != '\'' && symbol != '<')
	{
		return (has_arg ? rt_read_error('\"',
		"or '\'' or '<' => name argument", symbol) : NULL);
	}
	symbol = (symbol == '<') ? '>' : symbol;
	offset = p->index + 1;
	while (p->file[++p->index])
	{
		if ((p->index - offset) == OBJECT_NAME_MAXLENGTH)
			return ("Name argument is too long, max is 24 characters");
		if (p->file[p->index] == '\n')
			++p->line;
		else if (p->file[p->index] == symbol && ++p->index)
			return (NULL);
		result[p->index - offset] = p->file[p->index];
	}
	return (rt_read_error(symbol, "name arg terminating char", p->file[p->index]));
}

char		*rt_read_arg_number(t_rtparser *p, cl_float *result, char const *label)
{
	char	*number;

	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label, ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
		return (rt_read_error(':', "without spaces before vector '('", p->file[p->index]));
	if (p->file[++(p->index)] == '\0')
		return ("Expected number argument, reached end of file");
	else if (ft_isdigit(p->file[p->index]))
	{
		number = p->file + p->index;
		while (p->file[p->index] && (ft_isdigit(p->file[p->index]) ||
			p->file[p->index] == '.' || p->file[p->index] == 'e' || p->file[p->index] == 'E'))
			++(p->index);
		if (p->file[p->index] == '\n')
			p->line += 1;
		p->file[p->index] = '\0';
		++(p->index);
		*result = ft_str_to_f32(number);
		return (NULL);
	}
	return (rt_read_error('0', "or any other digit, for a number argument", p->file[p->index]));
}

static char	*rt_read_arg_vector_number(t_rtparser *p, cl_float *result, char sep)
{
	char	*file;
	char	*number;

	rt_read_whitespace(p);
	file = p->file;
	number = file + p->index;
	while (file[p->index] &&
		(ft_isdigit(file[p->index]) || file[p->index] == '.' ||
			file[p->index] == '+' || file[p->index] == '-' ||
			file[p->index] == 'e' || file[p->index] == 'E'))
		++(p->index);
	if (!file[p->index])
		return ("Unexpected end of file inside vector argument");
	rt_read_whitespace(p);
	if (file[p->index] != sep)
		return (rt_read_error(sep, "separator char", file[p->index]));
	file[p->index] = '\0';
	++(p->index);
	*result = ft_str_to_f32(number);
	return (NULL);
}

char		*rt_read_arg_vector(t_rtparser *p, cl_float3 *result, char const *label)
{
	char	*error;
	char	symbol;

	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label, ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
		return (rt_read_error(':', "without spaces before vector '('", p->file[p->index]));
	symbol = p->file[++(p->index)];
	if (symbol == '(' || symbol == '{' || symbol == '[')
		++(p->index);
	else
		return (rt_read_error('(', "or '{' or '[' => vector argument", symbol));
	symbol += (symbol == '(') ? 1 : 2;
	if ((error = rt_read_arg_vector_number(p, &(result->x), ',')))
		return (error);
	if ((error = rt_read_arg_vector_number(p, &(result->y), ',')))
		return (error);
	if ((error = rt_read_arg_vector_number(p, &(result->z), symbol)))
		return (error);
	return (NULL);
}

char		*rt_read_arg_color(t_rtparser *p, cl_float3 *result, char const *label)
{
	char	c;
	char	*str;
	t_u32	color;

	rt_read_whitespace(p);
	if ((c = p->file[p->index]) == '\0')
		return (NULL);
	else if (c == '#')
	{
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
		return (NULL);
	}
	else
	{
		str = rt_read_arg_vector(p, result, label);
		if (result->x < 0.)
			result->x = 0.;
		else if (result->x > 1.)
			result->x = 1.;
		if (result->y < 0.)
			result->y = 0.;
		else if (result->y > 1.)
			result->y = 1.;
		if (result->z < 0.)
			result->z = 0.;
		else if (result->z > 1.)
			result->z = 1.;
		return (str);
	}
}

char		*rt_read_arg_material(t_rtparser *p, t_material *result, char const *label)
{
	char const	*str;
	size_t		length;
	size_t		i;

	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label, ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
		return (rt_read_error(':', "without spaces before material string", p->file[p->index]));
	++(p->index);
	i = 0;
	while (i < MATERIALS)
	{
		str = rt_get_str_material((t_material)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_material)i;
			p->index += length;
			return (NULL);
		}
		++i;
	}
	return ("No valid material enum label encountered");
}

char		*rt_read_arg_pattern(t_rtparser *p, t_pattern *result, char const *label)
{
	char const	*str;
	size_t		length;
	size_t		i;

	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label, ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
		return (rt_read_error(':', "without spaces before texture pattern string", p->file[p->index]));
	++(p->index);
	i = 0;
	while (i < TEXTURE_PATTERNS)
	{
		str = rt_get_str_pattern((t_pattern)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_pattern)i;
			p->index += length;
			return (NULL);
		}
		++i;
	}
	return ("No valid texture pattern enum label encountered");
}


char		*rt_read_arg_projection(t_rtparser *p, t_uv_projection *result, char const *label)
{
	char const	*str;
	size_t		length;
	size_t		i;

	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label, ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
		return (rt_read_error(':', "without spaces before texture projection string", p->file[p->index]));
	++(p->index);
	i = 0;
	while (i < TEXTURE_PROJECTIONS)
	{
		str = rt_get_str_projection((t_uv_projection)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_uv_projection)i;
			p->index += length;
			return (NULL);
		}
		++i;
	}
	return ("No valid texture projection enum label encountered");
}