/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:02:45 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/18 21:25:05 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The call to ft_ptrarrnew might allocate more memory than necessary, but in
** the absence of a way to find the length of the va_list, this is an adequate
** solution. Extra space will be allocated in the following circumstances:
** presence of a %%, any succession of %x%y without a 'plain/literal' substring
** between the two %x substrings, the format being a single "%y" without any
** plain string next to it, etc. What we give is a linear upper bound, at most
** 2n+1 where n is the optimal number of strings allocated one could obtain by
** analysing the format string before allocating memory.
** Accounting for the null-term => 2n+1+1
*/
/*
** Maybe just read the string linearly ? With multiple whiles
*/

char		**format_to_strls(char const *fmt)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	if (!(result = ft_ptrarrnew(2 + 2 * ft_str_countchar(fmt, '%'))))
		return (NULL);
	k = -1;
	i = 0;
	while (fmt[i])
	{
		j = 1;
		if (fmt[i] == '%')
			while (fmt[i + j] && ft_in_base(fmt[i + j], ALL_SYMBOLS) != -1)
			{
				if (ft_in_base(fmt[i + ++j - 1], TYPES) != -1)
					break ;
			}
		else
			while (fmt[i + j] && fmt[i + j] != '%')
				++j;
		result[++k] = ft_strsub(fmt, i, j);
		i += j;
	}
	return (result);
}

t_format	read_format(char const *fmt_part)
{
	int			i;
	t_format	result;

	i = 1;
	result.flags = read_format_flags(fmt_part, &i);
	result.width = read_format_width(fmt_part, &i);
	result.prec = read_format_prec(fmt_part, &i);
	result.len_flag = read_format_len_flag(fmt_part, &i);
	result.type = read_format_type(fmt_part, &result, i);
	if (result.type == float_pt && result.prec == -1 &&
		result.type_char != 'a' && result.type_char != 'A')
		result.prec = 6;
	else if (result.type == float_pt && result.prec == 0 &&
			(result.type_char == 'g' || result.type_char == 'G'))
		result.prec = 1;
	return (result);
}

/*
** => ft_ivartoa_base was coded to force integer casting; memory would be
**		filled with ones rather than zeros in a few cases, and the called
**		variable should be of the right "signed" or "unsigned" type when it is
**		called.
*/

char		*ft_ivartoa_base(intmax_t n, char const *base, t_u8 bytes,
									t_u8 sign)
{
	t_varint	v;
	char		*res;

	v.sl = bytes == 8 ? (long)n : 0;
	if (bytes == 8)
		res = sign ? ft_imaxtoa_base(v.sl, base) : ft_uimaxtoa_base(v.ul, base);
	else if (bytes == 1)
	{
		v.sc = (char)n;
		res = sign ? ft_imaxtoa_base(v.sc, base) : ft_uimaxtoa_base(v.uc, base);
	}
	else if (bytes == 2)
	{
		v.ss = (short)n;
		res = sign ? ft_imaxtoa_base(v.ss, base) : ft_uimaxtoa_base(v.us, base);
	}
	else if (bytes == 4)
	{
		v.si = (int)n;
		res = sign ? ft_imaxtoa_base(v.si, base) : ft_uimaxtoa_base(v.ui, base);
	}
	else
		return (NULL);
	return (res);
}

int			convert_str(char const *fmt_part, t_list **a_lststr, va_list args)
{
	char		type;
	t_format	format_info;
	t_str		*result;

	if (fmt_part[0] != '%')
		result = str_to_t_str(fmt_part);
	else
	{
		type = fmt_part[ft_strlen(fmt_part) - 1];
		if (ft_in_base(type, TYPES) == -1)
			result = str_to_t_str(fmt_part);
		else
		{
			format_info = read_format(fmt_part);
			result = handle_format(format_info, fmt_part, args);
		}
	}
	if (!result || result->len == -1)
	{
		if (result)
			free(result);
		return (ERROR);
	}
	ft_lstappend(a_lststr, ft_lstnew_no_copy(result, sizeof(t_str)));
	return (OK);
}
