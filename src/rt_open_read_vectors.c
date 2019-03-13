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

void		rt_get_arg_number(t_rtparser *p, cl_float *result)
{
	char	*number;

	number = p->file + p->index;
	while (p->file[p->index] && (ft_isdigit(p->file[p->index]) ||
		p->file[p->index] == '.' || p->file[p->index] == 'e' ||
		p->file[p->index] == 'E'))
		++(p->index);
	if (p->file[p->index] == '\n')
		p->line += 1;
	p->file[p->index] = '\0';
	++(p->index);
	*result = ft_str_to_f32(number);
	return ;
}

char		*rt_read_arg_number(t_rtparser *p, cl_float *result,
			char const *label)
{
	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index,
		label, ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
	{
		return (rt_read_error(':', "without spaces before vector '('",
		p->file[p->index]));
	}
	if (p->file[++(p->index)] == '\0')
		return ("Expected number argument, reached end of file");
	else if (ft_isdigit(p->file[p->index]))
	{
		rt_get_arg_number(p, result);
		return (NULL);
	}
	return (rt_read_error('0', "or any other digit, for a number argument",
	p->file[p->index]));
}

static char	*rt_read_arg_vector_number(t_rtparser *p,
			cl_float *result, char sep)
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

char		*rt_read_arg_vector(t_rtparser *p, cl_float3 *result,
			char const *label)
{
	char	*error;
	char	symbol;

	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label,
		ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
	{
		return (rt_read_error(':', "without spaces before vector '('",
		p->file[p->index]));
	}
	symbol = p->file[++(p->index)];
	if (symbol == '(' || symbol == '{' || symbol == '[')
		++(p->index);
	else
		return (rt_read_error('(', "or '{' or '[' => vector argument", symbol));
	symbol += (symbol == '(') ? 1 : 2;
	if ((error = rt_read_arg_vector_number(p, &(result->x), ',')) ||
		(error = rt_read_arg_vector_number(p, &(result->y), ',')) ||
		(error = rt_read_arg_vector_number(p, &(result->z), symbol)))
		return (error);
	return (NULL);
}
