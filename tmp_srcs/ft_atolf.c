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

# define F64_MANTISSA_BITS				52
# define F64_EXP_BIAS					1023
# define F64_SIGNED_MANTISSA_MASK		0x800FFFFFFFFFFFFF
# define F64_EXP_MASK					0x7FF0000000000000
# define F64_INIT_VAL					0x1.p-52

# define F32_MANTISSA_BITS				23
# define F32_EXP_BIAS					127
# define F32_SIGNED_MANTISSA_MASK		0x807FFFFF
# define F32_EXP_MASK					0x7F800000
# define F32_INIT_VAL					0x1.p-23

//# define NOT_A_NUMBER					(0. / 0.)

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
/*	if ((exp = ft_atoi(s_exp)) > F64_EXP_BIAS)
		return ((s_mant[0] == '-' ? -1. : 1.) / 0.);
	else if (exp < 1 - F64_EXP_BIAS)
		return (0.);
*/	ro_tmp = s_mant + ft_strfind(s_mant, '.') + 1;
	if ((frac_digits = ft_strlen(ro_tmp)) > 0)
		exp -= frac_digits;
	result *= ft_lfpowi(10., exp); //replace with math.h powf
	free(tmp);
	return (result);// * (s_mant[0] == '-' && result == 0. ? -1. : 1.));
}

/*
** max_pow_ten is the power of ten to which the leftmost digit in the number
** corresponds.
** is made to only ever call expon_str_to_lf with a positive value and handles
** its own sign
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
	result *= F64_INIT_VAL * ft_lfpowi(2., (ft_strlen(tmp) - 1) * 4);
	if ((exp = ft_atoi(s_exp)) > F64_EXP_BIAS)
		return ((sign ? -1. : 1.) / 0.);
	else if (exp < 1 - F64_EXP_BIAS)
		return (0.);
	ft_memcpy(&mant, &result, sizeof(result));
	mant &= F64_SIGNED_MANTISSA_MASK;
	mant |= ((t_u64)(exp + F64_EXP_BIAS) << F64_MANTISSA_BITS) & F64_EXP_MASK;
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
		return (ft_strequ(str + (*str == '-'), "INF") ?
			(((*str == '-') * -1.) + 0.5) / 0. : 0. / 0.);
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
