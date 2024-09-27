/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils_rdfmt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:08:37 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/08 15:33:17 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_u8			read_format_flags(char const *fmt_part, int *i)
{
	t_u8	flags;
	char	c;

	flags = 0;
	if (ft_in_base(fmt_part[*i], FLAGS) == -1)
		return (FL_NONE);
	while (ft_in_base((c = fmt_part[*i]), FLAGS) != -1)
	{
		if (c == '+')
			flags |= FL_PLUS;
		else if (c == '-')
			flags |= FL_MINUS;
		else if (c == '#')
			flags |= FL_HASH;
		else if (c == '0')
			flags |= FL_ZERO;
		else if (c == ' ')
			flags |= FL_SPACE;
		else
			flags |= FL_ERROR;
		++(*i);
	}
	if ((flags & FL_SPACE) && (flags & FL_PLUS))
		flags -= FL_SPACE;
	return (flags);
}

int				read_format_width(char const *fmt_part, int *i)
{
	int		width;
	t_u8	digit;

	if (ft_in_base(fmt_part[*i], DECIM) == -1)
		return (-1);
	width = 0;
	while (ft_in_base(fmt_part[*i], DECIM) != -1)
	{
		digit = fmt_part[*i];
		width = width * 10 + digit - '0';
		++(*i);
	}
	return (width);
}

int				read_format_prec(char const *fmt_part, int *i)
{
	int		prec;
	t_u8	digit;
	t_u8	neg;

	if (fmt_part[*i] != '.')
		return (-1);
	++(*i);
	neg = 0;
	if (fmt_part[*i] == '-')
	{
		neg = 1;
		++(*i);
	}
	prec = 0;
	while (ft_in_base(fmt_part[*i], DECIM) != -1)
	{
		digit = fmt_part[*i];
		prec = prec * 10 + digit - '0';
		++(*i);
	}
	prec = neg ? -1 : prec;
	return (prec);
}

t_len_flag		read_format_len_flag(char const *fmt_part, int *i)
{
	char		len_flag_c;
	char		count;
	t_len_flag	result;

	if (ft_in_base(fmt_part[*i], LGTHS) == -1)
		return (no_len_flag);
	len_flag_c = fmt_part[*i];
	count = 1;
	++(*i);
	if (fmt_part[*i] == len_flag_c)
		(*i) += count++;
	else if (ft_in_base(fmt_part[*i], LGTHS) != -1)
		return (incoherent_len_flag);
	if (count == 2 && ((len_flag_c != 'l' && len_flag_c != 'h') ||
						(ft_in_base(fmt_part[*i], LGTHS) != -1)))
		return (incoherent_len_flag);
	if (count == 2)
		return (len_flag_c == 'l' ? fl_ll : fl_hh);
	result = len_flag_c == 'h' ? fl_h : no_len_flag;
	result = len_flag_c == 'l' ? fl_l : result;
	result = len_flag_c == 'j' ? fl_j : result;
	result = len_flag_c == 'z' ? fl_z : result;
	return (result);
}

t_types			read_format_type(char const *fmt_part, t_format *info, int i)
{
	char	c;
	t_types	result;

	c = fmt_part[i];
	info->type_char = c;
	result = c == '%' ? percent : no_type_error;
	result = c == 'd' || c == 'i' || c == 'D' ? int_dec : result;
	result = c == 'o' || c == 'O' ? int_uoct : result;
	result = c == 'u' || c == 'U' ? int_udec : result;
	result = c == 'x' || c == 'p' ? int_uhex_l : result;
	result = c == 'X' ? int_uhex_u : result;
	result = c == 'b' ? int_ubin_l : result;
	result = c == 'B' ? int_ubin_u : result;
	result = c == 'c' || c == 'C' ? uchar : result;
	result = c == 's' || c == 'S' || c == 'r' ? string : result;
	result = ft_strfind("aAeEfFgG", c) != -1 ? float_pt : result;
	info->len_flag = ft_strfind("DOUpCS", c) != -1 ? fl_l : info->len_flag;
	if (c == 'p')
		info->flags |= FL_HASH;
	return (result);
}
