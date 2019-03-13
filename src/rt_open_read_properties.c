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

char		*rt_get_arg_name(t_rtparser *p, char *result, char symbol)
{
	size_t	offset;

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
	return (rt_read_error(symbol, "name arg terminating char",
	p->file[p->index]));
}

char		*rt_read_arg_name(t_rtparser *p, char *result)
{
	t_bool	has_arg;
	char	symbol;

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
	return (rt_get_arg_name(p, result, symbol));
}

t_bool		rt_check_arg_bump_label(t_rtparser *p, t_bump *result)
{
	char const	*str;
	size_t		length;
	size_t		i;

	i = 0;
	while (i < BUMP_TYPES)
	{
		str = rt_get_str_bump((t_bump)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_bump)i;
			p->index += length;
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

char		*rt_read_arg_bump(t_rtparser *p, t_bump *result, char const *label)
{
	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label,
		ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
	{
		return (rt_read_error(':', "without spaces before bump string",
		p->file[p->index]));
	}
	++(p->index);
	if (rt_check_arg_bump_label(p, result))
		return (NULL);
	return ("No valid bump enum label encountered");
}
