/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_base_expn_to_base.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:57:39 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/25 17:57:42 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_str.h"
#include "libft_math.h"
#include "libft_io.h"

static char	*base_expn_char_to_base_digitstr(char c, char const *base_f,
											char const *base_t, t_u32 expn)
{
	char	*result;
	t_u32	radix_t;
	int		val;
	t_u32	i;

	result = ft_strnew(expn);
	val = ft_in_base(c, base_f);
	radix_t = ft_strlen(base_t);
	i = 0;
	while (i < expn)
	{
		result[expn - 1 - i] = base_t[val % radix_t];
		val /= radix_t;
		++i;
	}
	return (result);
}

static char	*convert_basen_to_base(char const *str, char const *base_f,
									char const *base_t, t_u32 expn)
{
	char	*result;
	char	*tmp;
	t_u32	i;

	result = NULL;
	i = 0;
	while (str[i])
	{
		tmp = base_expn_char_to_base_digitstr(str[i], base_f, base_t, expn);
		ft_strappend(&result, tmp);
		ft_strdel(&tmp);
		++i;
	}
	ft_strctrim_left_inplace(&result, base_t[0]);
	return (result);
}

char		*ft_str_base_expn_to_base(char const *str, char const *base_f,
									char const *base_t, t_u32 expn)
{
	int		i;

	if (!str || !base_f || !base_t ||
		!ft_is_valid_base(base_f) || !ft_is_valid_base(base_t) || expn == 0)
	{
		ft_putendl_fd("Invalid base combo given to str_base_expn_to_base.", 2);
		return (NULL);
	}
	i = (str[0] == '+' || str[0] == '-') - 1;
	while (str[++i])
		if (ft_in_base(str[i], base_f) == -1)
		{
			ft_putendl_fd("Str mismatches base in str_base_expn_to_base.", 2);
			return (NULL);
		}
	if (ft_ipowi(ft_strlen(base_t), expn) != ft_strlen(base_f))
	{
		ft_putendl_fd("Invalid exponent in str_base_expn_to_base.", 2);
		return (NULL);
	}
	if (expn == 1)
		return (ft_strdup(str));
	return (convert_basen_to_base(str, base_f, base_t, expn));
}
