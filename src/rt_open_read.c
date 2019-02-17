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
#include "libft_convert.h"

#include "../rt.h"

static char	*rt_read_arg_vector_number(t_rtparser *p, float *result, char sep)
{
	char	*file;
	char	*number;

	rt_read_whitespace(p);
	file = p->file;
	number = file + p->index;
	while (file[p->index] &&
		(ft_isdigit(file[p->index]) ||
			file[p->index] == '+' ||
			file[p->index] == '-' ||
			file[p->index] == '.'))
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

char		*rt_read_arg_vector(t_rtparser *p, cl_float3 *result)
{
	char	*error;
	char	symbol;

	rt_read_whitespace(p);
	if (!p->file[p->index])
		return ("Expected vector argument, reached end of file");
	symbol = p->file[p->index];
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

char		*rt_read_arg_number(t_rtparser *p, float *result)
{
	char	c;
	char	*file;
	char	*number;

	rt_read_whitespace(p);
	file = p->file;
	c = file[p->index];
	if (c == '\0')
		return ("Expected number argument, reached end of file");
	else if (ft_isdigit(c))
	{
		number = file + p->index;
		while (file[p->index] &&
			(ft_isdigit(file[p->index]) || file[p->index] == '.'))
			++(p->index);
		if (file[p->index] == '\n')
			p->line += 1;
		file[p->index] = '\0';
		++(p->index);
		*result = ft_str_to_f32(number);
		return (NULL);
	}
	return (rt_read_error('0', "or any other digit, for a number argument", c));
}

char		*rt_read_arg_color(t_rtparser *p, t_u32 *result)
{
	char	c;
	char	*file;
	char	*color;

	rt_read_whitespace(p);
	file = p->file;
	c = file[p->index];
	if (c == '\0')
		return ("Expected color argument, reached end of file");
	else if (c == '#')
	{
		++(p->index);
		color = file + p->index;
		while ((c = file[p->index]) && (ft_isdigit(c) ||
			('A' <= c && c <= 'F') || ('a' <= c && c <= 'f')))
			++(p->index);
		if (file[p->index] == '\n')
			p->line += 1;
		file[p->index] = '\0';
		++(p->index);
		*result = ft_hex_to_u32(color);
		return (NULL);
	}
	return (rt_read_error('#', "starting char for color arg", c));
}
