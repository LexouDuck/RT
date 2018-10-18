/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:33:14 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/29 01:49:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_polynomial.h"
#include "libft_io.h"

t_poly		polyobj_to_poly(char const *str)
{
	t_poly	result;
	char	**strls;
	int		i;

	strls = ft_split(str, "\t ");
	i = -1;
	while (strls[++i])
		result.coefs[i] = ft_atolf(strls[i]);
	result.deg = i - 1;
	ft_strlsdel(&strls);
	return (result);
}

char		*poly_to_str(t_poly *ro_poly)
{
	char	*res;
	char	*tmp;
	t_float	*coefs;
	int		i;

	res = NULL;
	tmp = NULL;
	i = ro_poly->deg;
	coefs = ro_poly->coefs;
	while (i >= 0)
	{
		ft_asprintf(&tmp, "%.3e x^%d + ", coefs[i], i);
		ft_strappend(&res, tmp);
		free(tmp);
		--i;
	}
	res[ft_strlen(res) - 7] = '\0';
	return (res);
}
