/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils_float_prec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:57:50 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/12 16:58:06 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** tmp arrives reversed for ease of iteration.
**
**    0	   6	index for res
** 0       9    index for tmp
** 99999.999	ft_strlen(tmp) 		= 9
**    99.999	reslen 				= 6
**   9 	    	'start' digit index	= 2 = 9 - 6 - 1, then
**    09.999	'++i, start + i'
*/
/*
** status should return 1 if an extra digit has been added
*/

static int	rounding_loop(char **a_res, char const *tmp,
							t_u32 reslen, char const *b)
{
	t_u32	i;
	t_u32	start;
	int		status;

	start = ft_strlen(tmp) - reslen;
	status = 0;
	i = 0;
	while ((*a_res)[i] == '0' || (*a_res)[i] == '.')
	{
		++i;
		if (tmp[start + i] == '.')
		{
			(*a_res)[i] = '.';
			continue ;
		}
		(*a_res)[i] = b[(ft_in_base(tmp[start + i], b) + 1) % ft_strlen(b)];
		if (i + 1 + (ft_strfind(tmp, '-') >= 0) == reslen && (*a_res)[i] == '0')
		{
			status = 1;
			(*a_res)[++i] = '1';
		}
	}
	while (++i <= ft_strlen(tmp))
		(*a_res)[i] = tmp[start + i - (status)];
	return (status);
}

static char	*round_up(char const *tmp, t_u32 reslen, char exp_c, int *status)
{
	char	*result;
	char	*base;
	t_u32	start;

	base = exp_c == 'p' ? HXLOW : DECIM;
	start = ft_strlen(tmp) - reslen - 1;
	if (exp_c != 'p' ? (ft_strfind("56789", tmp[start]) >= 0) :
							(ft_strfind("89abcdef", tmp[start]) >= 0))
	{
		result = ft_strnew(ft_strlen(tmp));
		result[0] = tmp[++start] == '.' ? '.' :
			base[(ft_in_base(tmp[start], base) + 1) % ft_strlen(base)];
		*status = rounding_loop(&result, tmp, reslen, base);
		ft_strrev_inplace(&result);
	}
	else
		result = ft_strrev(tmp);
	result[reslen + (*status && !exp_c)] = '\0';
	return (result);
}

static int	get_rounded_flstr(char **a_result, t_format info,
								char **a_flstr, char exp_c)
{
	char	*tmp;
	int		dotpos;
	int		status;

	tmp = ft_strcdup(*a_flstr, exp_c);
	dotpos = ft_strfind(tmp, '.');
	if ((status = dotpos + info.prec + 1 - ft_strlen(tmp)) < 0)
	{
		status = 0;
		ft_strrev_inplace(&tmp);
		*a_result = round_up(tmp, dotpos + info.prec + 1, exp_c, &status);
	}
	else
	{
		*a_result = ft_strpad_right(tmp, '0', status);
		status = 0;
	}
	ft_strdel(&tmp);
	if (ft_strfind("gG", info.type_char) >= 0
		&& (!(info.flags & FL_HASH) || info.prec == 1))
		ft_strctrim_right_inplace(a_result, '0');
	return (status);
}

/*
** - tmp : absolute representation of the string with convention to always have
**			a single zero before, reversed for ease of iteration in round_up
** - dotpos + cur_frac_digits == ft_strlen(tmp)
** - dotpos + info.prec + 1 = length of the result string
*/

int			apply_float_prec(t_format info, char **a_flstr, char exp_c)
{
	char	*result;
	char	*tmp;
	int		status;
	int		neg;

	result = NULL;
	status = get_rounded_flstr(&result, info, a_flstr, exp_c);
	if (status && exp_c)
	{
		neg = result[0] == '-';
		ft_swap(result + neg + 1, result + neg + 2, 1);
		tmp = ft_itoa(ft_atoi(ft_strchr(*a_flstr, exp_c) + 1) + 1);
		neg = tmp[0] == '-';
		ft_strinsert(&tmp, ft_strlen(tmp) - neg < 2 ? "0" : "", neg);
		ft_strprepend(tmp[0] == '-' ? "e" : "e+", &tmp);
	}
	else
		tmp = ft_strdup(ft_strchr(*a_flstr, exp_c));
	ft_strmerge(&result, &tmp);
	if ((info.prec == 0 || result[ft_strfind(result, '.') + 1] == exp_c)
		&& !(info.flags & FL_HASH))
		ft_strreplace_inplace(&result, ".", "");
	ft_strdel(a_flstr);
	*a_flstr = result;
	return (status);
}
