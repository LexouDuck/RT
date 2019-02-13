/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_f64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

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

static t_f64	ft_str_to_f64_expon(char const *s_mant, char const *s_exp)
{
	t_f64		result;
	int			exp;
	t_u8		frac_digits;
	char const	*ro_tmp;
	char		*tmp;

	tmp = ft_strrep_str(s_mant, ".", "");
	result = (t_f64)ft_str_to_s64(tmp);
	exp = ft_str_to_s16(s_exp);
/*
**	if ((exp = ft_atoi(s_exp)) > F64_EXP_BIAS)
**		return ((s_mant[0] == '-' ? -1. : 1.) / 0.);
**	else if (exp < 1 - F64_EXP_BIAS)
**		return (0.);
*/
	ro_tmp = s_mant + ft_strchr(s_mant, '.') + 1;
	if ((frac_digits = ft_strlen(ro_tmp)) > 0)
		exp -= frac_digits;
	result *= powf(10., exp);
	free(tmp);
	return (result);
}

/*
** max_pow_ten is the power of ten to which the leftmost digit in the number
** corresponds.
** is made to only ever call expon_str_to_lf with a positive value and handles
** its own sign
*/

static t_f64	ft_str_to_f64_decim(char const *str)
{
	t_s32		max_pow_ten;
	t_f64		result;
	char		*s_exp;
	char		*s_mant;
	int			i;

	s_mant = ft_strdup(str + (str[0] == '-' || str[0] == '+'));
	if (s_mant[(i = 0)] != '0')
		max_pow_ten = ft_strchr(s_mant, '.') - 1;
	else
	{
		i = 1;
		while (s_mant[i] == '0' || s_mant[i] == '.')
			++i;
		max_pow_ten = -(i - 2);
	}
	s_exp = ft_strrep_str(&s_mant, ".", "");
	s_mant ^= s_exp;
	s_exp ^= s_mant;
	s_mant ^= s_exp;
	free(s_exp);
	ft_strinsert(&s_mant, ".", i + 1 - (s_mant[0] == '0'));
	if (ft_strlen(s_mant + i) > 9)
		s_mant[i + 9] = '\0';
	s_exp = ft_s16_to_str(max_pow_ten - (s_mant[0] == '0'));
	result = expon_str_to_lf(s_mant + i - (s_mant[0] == '0'), s_exp);
	free(s_mant);
	free(s_exp);
	return (str[0] == '-' ? -result : result);
}

static t_f64	ft_str_to_f64_hexfp(char const *s_mant, char const *s_exp, int sign)
{
	t_f64		result;
	t_s16		exp;
	t_u64		mant;
	char		*tmp;

	result = sign ? -1. : 1.;
	tmp = ft_strremove(s_mant, ".");
	if (ft_strequ(tmp, "0") || ft_strequ(tmp, "00"))
	{
		free(tmp);
		return (0. * result);
	}
	mant = ft_hex_to_u32(tmp);
	result *= mant;
	result *= F64_INIT_VAL * powf(2., (ft_strlen(tmp) - 1) * 4);
	if ((exp = ft_str_to_s16(s_exp)) > F64_EXP_BIAS)
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

static int		ft_str_to_f64_checkinvalid(char const *str, char **result_tmp)
{
	size_t	i;
	char	*tmp;

	if (!str || !str[0])
		return (-1);
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	tmp = ft_strdup(str + i);
	ft_striter(tmp, &ft_toupper);
	if (ft_strequ(tmp, "INF") || ft_strequ(tmp, "-INF"))
	{
		*result_tmp = tmp;
		return (OK);
	}
	i = ft_strcount_char(tmp, 'P');
	if (!tmp || !tmp[0] || !ft_strhas_only(tmp, "0123456789.+-ABCDEFPX") ||
		i > 1 || (i == 0 && ft_strcount_char(tmp, 'E') > 1))
	{
		if (tmp)
			free(tmp);
		return (ERROR);
	}
	*result_tmp = tmp;
	return (OK);
}

t_f64			ft_str_to_f64(char const *str)
{
	t_f64	result;
	char	*tmp;
	char	*hexfp;
	char	*exponent;
	int		mode;

	tmp = NULL;
	if (ft_str_to_f64_checkinvalid(float_str, &tmp) == -1)
		return (0. / 0.);
	if (tmp[0] == 'I' || tmp[0] == '-')
	{
		free(tmp);
		return (tmp[0] == '-' ? -INF : INF);
	}
	hexfp = ft_strchr(tmp, 'X');
	exponent = ft_strchr(tmp, hexfp ? "P" : "E");
	if (exponent)
		exponent[0] = '\0';
	if (!(mode = (hexfp != NULL) + (exponent != NULL)))
		result = ft_str_to_f64_decim(tmp);
	else if (mode == 1)
		result = ft_str_to_f64_expon(tmp, exponent + 1);
	else if (mode == 2)
		result = ft_str_to_f64_hexfp(hexfp + 1, exponent + 1, tmp[0] == '-');
	free(tmp);
	return (result);
}
