/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:42:54 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:43:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/*
** Has some negligible error (beyond the seventh decimal digit; imprecision
** linked to input)
*/

static t_f64	expon_str_to_lf(char const *s_mant, char const *s_exp)
{
	t_f64		result;
	int			exp;
	t_u8		frac_digits;
	char const	*ro_tmp;
	char		*tmp;

	tmp = ft_strremove(s_mant, ".");
	result = (t_f64)ft_atoi(tmp);
	exp = ft_atoi(s_exp);
	ro_tmp = s_mant + ft_strfind(s_mant, '.') + 1;
	if ((frac_digits = ft_strlen(ro_tmp)) > 0)
		exp -= frac_digits;
	result *= ft_lfpowi(10., exp);
	free(tmp);
	return (result * (s_mant[0] == '-' && result == 0. ? -1. : 1.));
}

/*
** max_pow_ten is the power of ten to which the leftmost digit in the number
** corresponds.
*/

static t_f64	decim_str_to_lf(char const *str)
{
	t_s32		max_pow_ten;
	t_f64		result;
	char		*s_exp;
	char		*s_mant;
	int			i;

	s_mant = ft_strdup(str + (str[0] == '-' || str[0] == '+'));
	if (s_mant[(i = 0)] != '0')
		max_pow_ten = ft_strfind(s_mant, '.') - 1;
	else
	{
		i = 1;
		while (s_mant[i] == '0' || s_mant[i] == '.')
			++i;
		max_pow_ten = -(i - 2);
	}
	ft_strreplace_inplace(&s_mant, ".", "");
	ft_strinsert(&s_mant, ".", i + 1 - (s_mant[0] == '0'));
	if (ft_strlen(s_mant + i) > 9)
		s_mant[i + 9] = '\0';
	s_exp = ft_itoa(max_pow_ten - (s_mant[0] == '0'));
	result = expon_str_to_lf(s_mant + i - (s_mant[0] == '0'), s_exp);
	free(s_mant);
	free(s_exp);
	return (str[0] == '-' ? -result : result);
}

static t_f64	hexfp_str_to_lf(char const *s_mant, char const *s_exp, int sign)
{
	t_f64		result;
	int			exp;
	t_u64		mant;
	char		*tmp;

	result = sign ? -1. : 1.;
	tmp = ft_strremove(s_mant, ".");
	if (ft_strequ(tmp, "0") || ft_strequ(tmp, "00"))
	{
		free(tmp);
		return (0. * result);
	}
	mant = ft_atoui_base(tmp, HXUPP);
	result *= mant;
	result *= 0x1.p-52 * ft_lfpowi(2., (ft_strlen(tmp) - 1) * 4);
	exp = ft_atoi(s_exp);
	ft_memcpy(&mant, &result, sizeof(result));
	mant &= 0x800FFFFFFFFFFFFF;
	mant |= (t_u64)(exp + 1023) << 52;
	ft_memcpy(&result, &mant, sizeof(result));
	free(tmp);
	return (result);
}

static int		check_if_valid(char const *float_str, char **a_str)
{
	char	*str;

	if (!float_str || !(*float_str))
		return (-1);
	str = ft_strdup(float_str);
	ft_str_toupper(str);
	if (!str || !*str || !ft_str_containsonly(str, "0123456789.+-ABCDEFPX")
		|| ft_str_countchar(str, 'P') > 1
		|| (ft_str_countchar(str, 'P') == 0 && ft_str_countchar(str, 'E') > 1))
	{
		if (str)
			free(str);
		return (-1);
	}
	*a_str = str;
	return (0);
}

t_f64			ft_atolf(char const *float_str)
{
	char	*str;
	t_f64	result;
	char	**strls;
	int		mode;

	str = NULL;
	if (check_if_valid(float_str, &str) == -1)
		return (0. / 0.);
	strls = ft_split(str, ft_strfind(str, 'X') >= 0 ? "P" : "E");
	if (!(mode = ft_ptrarrlen(strls) + (ft_strfind(str, 'X') >= 0)))
	{
		ft_strlsdel(&strls);
		free(str);
		return (0. / 0.);
	}
	else if (mode == 1)
		result = decim_str_to_lf(strls[0]);
	else if (mode == 2)
		result = expon_str_to_lf(strls[0], strls[1]);
	else
		result = hexfp_str_to_lf((strls[0]) + ft_strfind(strls[0], 'X') + 1,
					strls[1], strls[0][0] == '-');
	ft_strlsdel(&strls);
	free(str);
	return (result);
}
