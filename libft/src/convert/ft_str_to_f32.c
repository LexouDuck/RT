/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_str_to_f32.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../libft_convert.h"
#include "../../libft_memory.h"
#include "../../libft_string.h"

/*
** Has some negligible error (beyond the seventh decimal digit; imprecision
** linked to input)
*/

static t_f32	ft_str_to_f32_expon(char const *s_mant, char const *s_exp)
{
	t_f32		result;
	t_s16		exponent;
	size_t		frac_digits;
	char		*tmp;

	tmp = ft_strremove(s_mant, ".");
	result = (t_f32)ft_str_to_s32(tmp);
	free(tmp);
	exponent = 0;
	if (s_exp)
	{
		exponent = ft_str_to_s16(s_exp);
		if (exponent > F32_EXP_BIAS)
			return (s_mant[0] == '-' ? -INFINITY : INFINITY);
		else if (exponent < 1 - F32_EXP_BIAS)
			return (0.);
	}
	tmp = ft_strchr(s_mant, '.');
	if (tmp && (frac_digits = ft_strlen(tmp + 1)) > 0)
			exponent -= frac_digits;
	result *= powf(10., exponent);
	return (result);
}

static t_f32	ft_str_to_f32_hexfp(
	char const *s_mant,
	char const *s_exp,
	int sign)
{
	t_f32		result;
	t_s16		exponent;
	t_u32		mant;
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
	result *= F32_INIT_VAL * powf(2., (ft_strlen(tmp) - 1) * 4);
	if ((exponent = ft_str_to_s16(s_exp)) > F32_EXP_BIAS)
		return ((sign ? -1. : 1.) / 0.);
	else if (exponent < 1 - F32_EXP_BIAS)
		return (0.);
	ft_memcpy(&mant, &result, sizeof(result));
	mant &= F32_SIGNED_MANTISSA_MASK;
	mant |= ((t_u32)(exponent + F32_EXP_BIAS) << F32_MANTISSA_BITS) & F32_EXP_MASK;
	ft_memcpy(&result, &mant, sizeof(result));
	free(tmp);
	return (result);
}

t_f32			ft_str_to_f32(char const *str)
{
	t_f32	result;
	char	*tmp;
	char	*hexfp;
	char	*exponent;
	int		mode;

	tmp = NULL;
	if (ft_str_to_float_checkinvalid(str, &tmp))
		return (NOT_A_NUMBER);
	if (tmp[0] == 'I' || (tmp[0] == '-' && tmp[0] == 'I'))
	{
		free(tmp);
		return (tmp[0] == '-' ? -INFINITY : INFINITY);
	}
	hexfp = ft_strchr(tmp, 'X');
	exponent = ft_strchr(tmp, (hexfp ? 'P' : 'E'));
	if (exponent)
		*(exponent++) = '\0';
	if (!(mode = (hexfp != NULL) + (exponent != NULL)))
		result = ft_str_to_f32_expon(tmp, NULL);
	else if (mode == 1)
		result = ft_str_to_f32_expon(tmp, exponent);
	else if (mode == 2)
		result = ft_str_to_f32_hexfp(hexfp + 1, exponent, tmp[0] == '-');
	free(tmp);
	return (result);
}
