/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_utils_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:18:27 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 16:54:22 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 0x7F = 127, 0x7FF = 2047, 0xFFFF = 65535
** Also, for 0b11000000 = 0xC0, 0b11100000 = 0xE0 and 0b11110000 = 0xF0,
** 1 << size is 2^size, -1 makes it 00000111 with as many 1s as size, bitshift
** left (8 - size) gives the result we want.
** mod 0x40 => extract six last digits.
**
** Standard calls this wcrtomb, wide char to multibyte
*/

static char		*encode_unicodepoint_to_utf8(wchar_t c)
{
	t_u32	size;
	char	*utf8_c;

	if (c > 0x10FFFF)
		return (NULL);
	size = 1 + (c > 0x7F) + (c > 0x7FF) + (c > 0xFFFF);
	if (size > (t_u32)MB_CUR_MAX)
		return ("MB_CUR_MAX_ERROR");
	if (!(utf8_c = ft_strnew(size)))
		return (NULL);
	utf8_c[0] = size > 1 ? ((0x1 << size) - 1) << (8 - size) : 0;
	while (--size)
	{
		utf8_c[size] = 0x80 | c % 0x40;
		c /= 0x40;
	}
	utf8_c[0] |= c;
	return (utf8_c);
}

/*
** Maybe make a single malloc of size_t (4 * len(unicode_str)) for utf8_str,
** use strcat intelligently, then another single malloc once final size_t is
** known ? strappend so often would probably be quite computation-hungry.
** See how this affects performance in the end.
*/

static char		*build_utf8(wchar_t *unicode_str)
{
	char	*utf8_str;
	char	*new_char;
	int		i;

	if (!unicode_str || !(utf8_str = ft_strnew(0)))
		return (NULL);
	i = 0;
	while (unicode_str[i])
	{
		new_char = encode_unicodepoint_to_utf8(unicode_str[i]);
		if (new_char == NULL || ft_strequ(new_char, "MB_CUR_MAX_ERROR"))
		{
			free(utf8_str);
			return (new_char);
		}
		ft_strappend(&utf8_str, new_char);
		free(new_char);
		++i;
	}
	return (utf8_str);
}

/*
** FL_ZERO doesn't apply to strings
*/

t_str			*handle_str_type(t_format info, va_list args)
{
	char	*str;
	t_str	*result;

	str = info.len_flag == fl_l ? build_utf8((wchar_t*)va_arg(args, wchar_t*)) :
									ft_strdup((char*)va_arg(args, char*));
	if (!str || ft_strequ(str, "MB_CUR_MAX_ERROR"))
		return (str_to_t_str(str ? NULL : "(null)"));
	if (!(result = (t_str*)malloc(sizeof(t_str))))
		return (NULL);
	if (info.prec != -1 && (t_u64)info.prec < ft_strlen(str))
	{
		if (info.len_flag == fl_l)
			while ((t_u8)str[info.prec] >> 6 == (t_u8)0x2)
				--info.prec;
		str[info.prec] = '\0';
	}
	if (info.width != -1 && info.width > (int)ft_strlen(str))
		(info.flags & FL_MINUS) ?
			ft_strpad_right_inplace(&str, ' ', info.width - ft_strlen(str)) :
			ft_strpad_left_inplace(&str, ' ', info.width - ft_strlen(str));
	result->data = info.type_char == 'r' ? ft_str_toprint(str) : ft_strdup(str);
	ft_strdel(&str);
	result->len = ft_strlen(result->data);
	return (result);
}

t_str			*handle_uchar_type(t_format info, va_list args)
{
	t_str	*result;
	char	*s;

	if (info.len_flag == fl_l)
		if (!(s = encode_unicodepoint_to_utf8((wchar_t)va_arg(args, wchar_t)))
			|| ft_strequ(s, "MB_CUR_MAX_ERROR"))
			return (str_to_t_str(NULL));
	if (info.len_flag != fl_l)
		s = ft_strcnew(1, (char)va_arg(args, int));
	result = (t_str*)malloc(sizeof(t_str));
	result->len = ft_max(ft_strlen(s) + !s[0], info.width);
	if (info.width != -1 && info.width > (int)ft_strlen(s))
	{
		if ((info.flags & FL_MINUS) && *s)
			ft_strpad_right_inplace(&s, ' ', info.width - ft_strlen(s));
		else if ((info.flags & FL_MINUS))
		{
			ft_strpad_right_inplace(&s, ' ', info.width);
			*s = '\0';
		}
		else
			ft_strpad_left_inplace(&s, ' ', info.width - ft_strlen(s) - !*s);
	}
	result->data = s;
	return (result);
}
