/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_str_to_float.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"
#include "../../libft_char.h"
#include "../../libft_string.h"

static char	*ft_str_to_float_toupper(char const *str)
{
	char	*result;
	size_t	end;
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	end = ft_strlen(str) - 1;
	while (!ft_isdigit(str[end]))
		--end;
	result = ft_strsub(str, i, 1 + end - i);
	i = 0;
	while (result[i])
	{
		result[i] = ft_toupper(result[i]);
		++i;
	}
	return (result);
}

int			ft_str_to_float_checkinvalid(char const *str, char **result_tmp)
{
	char	*tmp;
	size_t	count_p;
	size_t	count_e;

	if (str[0] == '\0')
		return (ERROR);
	tmp = ft_str_to_float_toupper(str);
	if (ft_strequ(tmp, "INF") || ft_strequ(tmp, "-INF") ||
		ft_strequ(tmp, "INFINITY") || ft_strequ(tmp, "-INFINITY"))
	{
		*result_tmp = tmp;
		return (OK);
	}
	count_p = ft_strcount_char(tmp, 'P');
	count_e = ft_strcount_char(tmp, 'E');
	if (!tmp || !tmp[0] || !ft_strhasonly(tmp, "0123456789.+-ABCDEFXP") ||
		count_p > 1 || (count_p == 0 && count_e > 1))
	{
		if (tmp)
			free(tmp);
		return (ERROR);
	}
	*result_tmp = tmp;
	return (OK);
}

/*
** max_pow_ten is the power of ten to which the leftmost digit in the number
** corresponds.
** is made to only ever call expon_str_to_lf with a positive value and handles
** its own sign
*/
/*
t_f64	ft_str_to_f64_decim(char const *str)
{
	t_s64		max_pow_ten;
	t_f64		result;
	char		*s_exp;
	char		*s_mant;
	int			i;

	s_mant = ft_strdup(str + (str[0] == '-' || str[0] == '+'));
	i = 0;
	if (s_mant[i] != '0')
	{
		s_exp = ft_strchr(s_mant, '.');
		s_exp = (s_exp ? (char *)(s_exp - s_mant) : NULL);
		max_pow_ten = (size_t)s_exp - 1;
	}
	else
	{
		i = 1;
		while (s_mant[i] == '0' || s_mant[i] == '.')
			++i;
		max_pow_ten = -(i - 2);
	}
	s_exp = s_mant;
	s_mant = ft_strremove(s_mant, ".");
	free(s_exp);
	s_exp = s_mant;
	s_mant = ft_strinsert(s_exp, ".", i + 1 - (s_mant[0] == '0'));
	free(s_exp);
	if (ft_strlen(s_mant + i) > 9)
		s_mant[i + 9] = '\0';
	s_exp = ft_s16_to_str(max_pow_ten - (s_mant[0] == '0'));
	result = ft_str_to_f64_expon(s_mant + i - (s_mant[0] == '0'), s_exp);
	free(s_mant);
	free(s_exp);
	return (str[0] == '-' ? -result : result);
}
*/
