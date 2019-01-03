/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpolynom_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:33:14 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/29 01:49:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_polynomial.h"
#include "libft_io.h"

t_cpoly		polyobj_to_cpoly(char const *str)
{
	t_cpoly		result;
	char		**strls;
	int			i;
	t_complex	tmp;

	ft_bzero(result.coefs, sizeof(t_complex) * (MAX_DEGREE + 1));
	strls = ft_split(str, "\t ");
	i = 0;
	while (strls[i])
	{
		tmp.re = ft_atolf(strls[i]);
		if (strls[i + 1])
			tmp.im = ft_atolf(strls[i + 1]);
		else
		{
			tmp.im = 0.;
			result.coefs[i / 2] = tmp;
			break ;
		}
		result.coefs[i / 2] = tmp;
		i += 2;
	}
	result.deg = (i % 2) ? (i / 2) : (i / 2 - 1);
	ft_strlsdel(&strls);
	return (result);
}

char		*cpoly_to_polyobj(t_cpoly *ro_cpoly)
{
	char		*res;
	char		*tmp;
	t_complex	*coefs;
	int			i;

	tmp = NULL;
	res = NULL;
	i = 0;
	coefs = ro_cpoly->coefs;
	while (i <= ro_cpoly->deg)
	{
		ft_asprintf(&tmp, "%a %a\t\t", coefs[i].re, coefs[i].im);
		ft_strappend(&res, tmp);
		free(tmp);
		++i;
	}
	res[ft_strlen(res) - 2] = '\0';
	return (res);
}

char		*cpoly_to_str(t_cpoly *ro_cpoly)
{
	char		*res;
	char		*tmp;
	t_complex	*coefs;
	int			i;

	tmp = NULL;
	res = NULL;
	i = ro_cpoly->deg;
	coefs = ro_cpoly->coefs;
	while (i >= 0)
	{
		ft_asprintf(&tmp, "(%.3e + i*%.3e) z^%d + ",
						coefs[i].re, coefs[i].im, i);
		ft_strappend(&res, tmp);
		free(tmp);
		--i;
	}
	res[ft_strlen(res) - 7] = '\0';
	return (res);
}

char		*cpolyfrac_to_str(t_cpolyfrac *ro_cpf)
{
	char	*str;
	char	*den;
	char	*num;

	str = NULL;
	num = cpoly_to_str(&(ro_cpf->num));
	den = cpoly_to_str(&(ro_cpf->den));
	ft_asprintf(&str, "num: %s /\nden: %s", num, den);
	free(num);
	free(den);
	return (str);
}
