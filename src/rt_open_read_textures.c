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

t_bool		rt_check_arg_pattern_label(t_rtparser *p, t_pattern *result)
{
	char const	*str;
	size_t		length;
	size_t		i;

	i = 0;
	while (i < TEXTURE_PATTERNS)
	{
		str = rt_get_str_pattern((t_pattern)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_pattern)i;
			p->index += length;
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

char		*rt_read_arg_pattern(t_rtparser *p, t_pattern *result,
			char const *label)
{
	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label,
		ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
	{
		return (rt_read_error(':', "without spaces before texture"
		" pattern string", p->file[p->index]));
	}
	++(p->index);
	if (rt_check_arg_pattern_label(p, result))
		return (NULL);
	return ("No valid texture pattern enum label encountered");
}

t_bool		rt_check_arg_projection_label(t_rtparser *p, t_projection *result)
{
	char const	*str;
	size_t		length;
	size_t		i;

	i = 0;
	while (i < TEXTURE_PROJECTIONS)
	{
		str = rt_get_str_projection((t_projection)i);
		length = ft_strlen(str);
		if (ft_strnequ(p->file + p->index, str, length))
		{
			*result = (t_projection)i;
			p->index += length;
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

char		*rt_read_arg_projection(t_rtparser *p, t_projection *result,
			char const *label)
{
	rt_read_whitespace(p);
	if (!p->file[p->index] || !ft_strnequ(p->file + p->index, label,
		ft_strlen(label)))
		return (NULL);
	p->index += ft_strlen(label);
	if (p->file[p->index] != ':')
	{
		return (rt_read_error(':', "without spaces before texture"
		" projection string", p->file[p->index]));
	}
	++(p->index);
	if (rt_check_arg_projection_label(p, result))
		return (NULL);
	return ("No valid texture projection enum label encountered");
}
