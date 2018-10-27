/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 19:14:43 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_apa.h"

/*
** https://stackoverflow.com/questions/3215235/how-do-you-print-the-exact
** 											-value-of-a-floating-point-number
*/

static void		float_info_to_float_binstrs(char ***a_res,
							int exp_b2, t_u64 mantissa)
{
	char	*tmp;

	tmp = ft_uitoa_base(mantissa, BINAR);
	ft_strpad_left_inplace(&tmp, '0', 53 - ft_strlen(tmp));
	if (0 <= exp_b2 && exp_b2 < 52)
	{
		ft_strinsert(&tmp, ".", exp_b2 + 1);
		ft_strctrim_right_inplace(&tmp, '0');
		if (tmp[ft_strlen(tmp) - 1] == '.')
			ft_strappend(&tmp, "0");
	}
	else if (exp_b2 < 0)
	{
		ft_strpad_left_inplace(&tmp, '0', -exp_b2 - 1);
		ft_strctrim_right_inplace(&tmp, '0');
		ft_strprepend(ft_strequ(tmp, "") ? "0.0" : "0.", &tmp);
	}
	else
	{
		ft_strpad_right_inplace(&tmp, '0', exp_b2 - 52);
		ft_strappend(&tmp, ".0");
	}
	*a_res = ft_split(tmp, ".");
	ft_strdel(&tmp);
}

static char		*ft_lftoa_hexfp(int exp_b2, t_u64 mantissa)
{
	char	*result;
	char	*tmp;

	tmp = ft_itoa(exp_b2);
	if (tmp[0] != '-' && ft_strlen(tmp) < 2)
		ft_strprepend("+", &tmp);
	else if (tmp[0] != '-')
		ft_strprepend("+", &tmp);
	ft_strpad_left_inplace(&tmp, 'p', 1);
	result = tmp;
	tmp = ft_uitoa_base(mantissa, HXLOW);
	ft_strpad_left_inplace(&tmp, '0', 14 - ft_strlen(tmp));
	ft_strctrim_right_inplace(&tmp, '0');
	if (ft_strequ(tmp, "") || ft_strequ(tmp, "-"))
		tmp[(tmp[0] == '-')] = '0';
	ft_strinsert(&tmp, ".", (tmp[0] == '-') + 1);
	if (tmp[ft_strlen(tmp) - 1] == '.')
		ft_strappend(&tmp, "0");
	ft_strprepend(tmp, &result);
	ft_strinsert(&result, "0x", result[0] == '-');
	free(tmp);
	return (result);
}

static char		*ft_lftoa_fp(char **bin_strs)
{
	char	*result;
	char	*tmp;
	t_u32	frac_digits;
	t_vlq	vlq;
	t_vlq	pow10;

	vlq = ft_atovlq(bin_strs[0], BINAR);
	tmp = ft_vlqtoa_base(vlq, DECIM);
	result = ft_strpad_right(tmp, '.', 1);
	ft_strdel(&tmp);
	ft_vlqdel(&vlq);
	vlq = ft_atovlq(bin_strs[1], BINAR);
	frac_digits = ft_strlen(bin_strs[1]);
	pow10 = ft_vlq_getpow10(frac_digits);
	ft_vlq_mul_acc(&vlq, pow10);
	ft_vlq_bsr_acc(&vlq, frac_digits);
	tmp = ft_vlqtoa_base(vlq, DECIM);
	ft_strpad_left_inplace(&tmp, '0', frac_digits - ft_strlen(tmp));
	ft_strmerge(&result, &tmp);
	ft_vlqdel(&pow10);
	ft_vlqdel(&vlq);
	return (result);
}

/*
** a*2^b = c*10^d with 1 <= a < 2 and 1 <= c < 10
** => d = floor(log10(a*2^b)) = floor(log10(a) + b * log10(2));
*/

static char		*ft_lftoa_exp(char **bin_strs)
{
	char	*result;
	char	*tmp;
	int		exp_b10;
	int		i;

	if (ft_strequ((tmp = ft_lftoa_fp(bin_strs)), "0.0"))
	{
		ft_strappend(&tmp, "e+00");
		return (tmp);
	}
	i = 0;
	if ((exp_b10 = ft_strfind(tmp, '.')) == 1)
		while (tmp[2 + i] == '0')
			++i;
	exp_b10 = exp_b10 == 1 && tmp[2 + i] ? -i - (tmp[0] == '0') : exp_b10 - 1;
	result = ft_itoa(exp_b10);
	if (ft_strlen(result) < 3 && result[0] == '-')
		ft_strinsert(&result, "0", 1);
	else if (result[0] != '-')
		ft_strprepend(ft_strlen(result) == 1 ? "+0" : "+", &result);
	ft_strpad_left_inplace(&result, 'e', 1);
	ft_strmerge(&tmp, &result);
	ft_strreplace_inplace(&result, ".", "");
	ft_strctrim_left_inplace(&result, '0');
	return (ft_strinsert(&result, ".", 1));
}

char			*ft_lftoa(double lf, char style)
{
	char	*result;
	t_u64	extract;
	int		exp_b2;
	t_u64	mantissa;
	char	**bin_strs;

	ft_memcpy(&extract, &lf, sizeof(t_u64));
	if (lf != lf)
		return (ft_strdup(ft_msb(extract) ? "-nan" : "nan"));
	mantissa = ((extract << 12) >> 12);
	if ((exp_b2 = ((extract << 1) >> 53) - 1023) == 1024)
		return (ft_strdup(ft_msb(extract) ? "-inf" : "inf"));
	if (exp_b2 != -1023)
		mantissa |= 0x10000000000000;
	else
		exp_b2 = lf == 0. ? 0 : exp_b2 + 1;
	bin_strs = NULL;
	float_info_to_float_binstrs(&bin_strs, exp_b2, mantissa);
	result = style == 'p' ? ft_lftoa_hexfp(exp_b2, mantissa) : NULL;
	result = style == 'e' ? ft_lftoa_exp(bin_strs) : result;
	result = style == '\0' ? ft_lftoa_fp(bin_strs) : result;
	if (extract >> 63)
		ft_strprepend("-", &result);
	ft_strlsdel(&bin_strs);
	return (result);
}
