/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils_float.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:57:50 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/26 16:10:24 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** strfind(src, 'n') returns true only for nan and inf
*/

static void	apply_float_width(t_format info, char **a_flstr)
{
	int		start;
	int		size;

	if ((info.flags & (FL_SPACE | FL_PLUS)) && (*a_flstr)[0] != '-')
		ft_strprepend(info.flags & FL_SPACE ? " " : "+", a_flstr);
	size = ft_strlen(*a_flstr);
	start = ft_in_base('x', (*a_flstr));
	start += (start == -1) ? 1 + (**a_flstr == '-') : 1;
	if (info.width > size && (info.flags & FL_MINUS))
		ft_strpad_right_inplace(a_flstr, ' ', info.width - size);
	else if (info.width > size &&
				(!(info.flags & (FL_MINUS | FL_ZERO)) ||
				ft_strfind(*a_flstr, 'n') >= 0))
		ft_strpad_left_inplace(a_flstr, ' ', info.width - size);
	else if (info.width > size)
		ft_strpad_insert_inplace(a_flstr, '0', start, info.width - size);
}

static char	*handle_aef_type(t_format info, double lf)
{
	char	*result;
	char	exp_c;

	exp_c = info.type_char == 'e' || info.type_char == 'E' ? 'e' : 'p';
	exp_c = info.type_char == 'f' || info.type_char == 'F' ? '\0' : exp_c;
	result = ft_lftoa(lf, exp_c);
	if (!ft_strequ(result, "inf") && !ft_strequ(result, "-inf") &&
		!ft_strequ(result, "nan") && !ft_strequ(result, "-nan") &&
		info.prec != -1)
		apply_float_prec(info, &result, exp_c);
	ft_strreplace_inplace(&result, ".0p", info.flags & FL_HASH ? ".p" : "p");
	if ((info.flags & FL_HASH) && ft_in_base('.', result) == -1 &&
			ft_in_base('n', result) == -1)
		ft_strinsert(&result, ".", ft_in_base(exp_c, result));
	apply_float_width(info, &result);
	return (result);
}

static char	*handle_g_type(t_format info, double lf)
{
	char	*result;
	int		exp_b10;
	int		boolxp;

	if (ft_strfind((result = ft_lftoa(lf, 'e')), 'n') == -1)
	{
		exp_b10 = ft_atoi(ft_strrchr(result, 'e') + 1);
		if (!(boolxp = (exp_b10 < -4 || info.prec <= exp_b10) && lf != 0))
		{
			ft_strdel(&result);
			result = ft_lftoa(lf, '\0');
		}
		info.prec = info.prec - 1 - ((!boolxp) * (exp_b10));
		if ((exp_b10 = apply_float_prec(info, &result, boolxp ? 'e' : '\0'))
			&& !(info.flags & FL_HASH) && boolxp)
		{
			ft_strreplace_inplace(&result, "0e", "e");
			ft_strreplace_inplace(&result, ".e", "e");
		}
		if ((info.flags & FL_HASH) && ft_in_base('.', result) == -1 &&
				ft_in_base('n', result) == -1)
			ft_strinsert(&result, ".", ft_in_base(boolxp ? 'e' : '\0', result));
	}
	apply_float_width(info, &result);
	return (result);
}

/*
** Example debug value:
**
** in hex_fp : -0x1.123456789abcdp+1010
** in memory :	cdab8967452311ff (little endian)
** in hex:		ff1123456789abcd
** in binary : 1111111100010001001000110100010101100111100010011010101111001101
**	where:
** 		sign =	1
** 		exp =	11111110001 (1010 + 1023 is 11111110001 in binary; 11 b)
**			 	7F1 (hex)
** 		mantissa = 0001001000110100010101100111100010011010101111001101 (52 b)
**				   123456789ABCD
**
** 	struct lconv	*lc;
**
**	lc = localeconv();
**	if (*(lc->decimal_point) != '.')
**		ft_strreplace_inplace(&tmp, ".", lc->decimal_point);
*/

t_str		*handle_float_type(t_format info, va_list args)
{
	double			lf;
	char			*tmp;
	t_str			*result;

	lf = va_arg(args, double);
	if (ft_strfind("aAeEfF", info.type_char) >= 0)
		tmp = handle_aef_type(info, lf);
	else if (info.type_char == 'g' || info.type_char == 'G')
		tmp = handle_g_type(info, lf);
	else
		tmp = ft_strdup("(float_handler_error)");
	if (MAC_OS && ft_strequ(tmp, "-nan"))
		ft_strreplace_inplace(&tmp, "-", "");
	if (ft_strfind("AFEG", info.type_char) >= 0)
		ft_str_toupper(tmp);
	result = str_to_t_str(tmp);
	free(tmp);
	return (result);
}
