/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atovlq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 02:11:16 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:30 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** parsing string from left to right (with reverse and reverse iteration because
** of norminette limiting variables, adding to vlq by higher powers first
*/

static t_vlq		bin_atovlq(char const *a)
{
	t_vlq	result;
	char	*tmp;
	t_u32	size;
	t_u32	i;
	int		j;

	if (a[0] == '0' && a[1] == '\0')
		return (ft_vlqnew(1));
	tmp = ft_strdup(a);
	ft_strctrim_left_inplace(&tmp, '0');
	ft_strpad_left_inplace(&tmp, '0', (63 - (ft_strlen(tmp) % 63)) % 63);
	size = ft_strlen(tmp) / 63;
	result = ft_vlqnew(size);
	i = 0;
	while (i < size)
	{
		j = -1;
		while (++j < 63)
			if (tmp[i * 63 + j] == '1')
				result[i] |= (0x4000000000000000 >> j);
		++i;
	}
	ft_strdel(&tmp);
	return (result);
}

static t_vlq		anybase_atovlq(char const *a, char const *base,
									t_vlq *radix)
{
	t_vlq	result;
	int		i;
	int		len;
	t_vlq	val;
	t_vlq	base_pow;

	i = (a[0] == '+' || a[0] == '-') - 1;
	len = ft_strlen(a);
	result = ft_vlqnew(1);
	base_pow = ft_vlqnew(1);
	base_pow[0] = 1;
	while (i < --len)
	{
		val = ft_vlqnew(1);
		val[0] = ft_in_base(a[len], base);
		ft_vlq_mul_acc(&val, base_pow);
		ft_vlq_add_acc(&result, val);
		ft_vlq_mul_acc(&base_pow, *radix);
		ft_vlqdel(&val);
	}
	ft_vlqdel(&base_pow);
	ft_vlqdel(radix);
	return (result);
}

static t_vlq		nbin_atovlq(char const *a, char const *base,
								t_u32 pow_radix)
{
	t_vlq	result;
	char	*bin;
	char	*tmp;
	t_u32	i;
	t_u8	j;

	bin = NULL;
	i = 0;
	while (a[i])
	{
		j = 0;
		tmp = ft_strnew(pow_radix);
		while (j < pow_radix)
		{
			tmp[j] = (ft_in_base(a[i], base) >> (pow_radix - 1 - j)) % 2 ?
						'1' : '0';
			++j;
		}
		ft_strmerge(&bin, &tmp);
		++i;
	}
	result = bin_atovlq(bin);
	ft_strdel(&bin);
	return (result);
}

/*
** nbstr in input are in normal order, not rev.
** leading + and - are ignored; internal + and - cause error.
*/

t_vlq				ft_atovlq(char const *a, char const *base)
{
	int		i;
	t_vlq	radix_vlq;

	if (!ft_is_valid_base(base))
	{
		ft_putendl_fd("Invalid base given to atovlq.", 2);
		return (NULL);
	}
	i = (a[0] == '+' || a[0] == '-') - 1;
	while (a[++i])
		if (ft_in_base(a[i], base) == -1)
		{
			ft_putendl_fd("Digit and base mismatch in atovlq.", 2);
			return (NULL);
		}
	if (ft_strequ(base, BINAR))
		return (bin_atovlq(a));
	else if ((i = ft_ilog2(ft_strlen(base))) != -1)
		return (nbin_atovlq(a, base, i));
	else
	{
		radix_vlq = ft_vlqnew(1);
		radix_vlq[0] = ft_strlen(base);
		return (anybase_atovlq(a, base, &radix_vlq));
	}
}
