/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:35:48 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_atoi_base_indexof(char const *base, char c)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

static int	ft_atoi_check_base(char const *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		++i;
	}
	return (i < 2 ? 0 : i);
}

static int	ft_atoi_base_get_offset(
			char const *str,
			char const *base)
{
	int i;

	i = 0;
	while (str[i] && ft_atoi_base_indexof(base, str[i]) == -1)
	{
		if (str[i] == '-')
		{
			i += 1;
			return (i * -1);
		}
		if (str[i] == '+')
		{
			i += 1;
			return (i);
		}
		++i;
	}
	return (i);
}

static int	ft_atoi_base_get_result(
			char const *str,
			char const *base,
			int length,
			int base_n)
{
	int	result;
	int	digit_n;
	int	digit;
	int	i;

	result = 0;
	digit_n = 1;
	i = 0;
	while (i < length)
	{
		digit = ft_atoi_base_indexof(base, str[length - 1 - i]);
		if (digit == -1)
			return (0);
		result += (digit * digit_n);
		digit_n *= base_n;
		++i;
	}
	return (result);
}

int			ft_atoi_base(
			char const *str,
			char const *base)
{
	int base_n;
	int	offset;
	int	length;
	int	negative;

	if (str == NULL || base == NULL)
		return (0);
	base_n = ft_atoi_check_base(base);
	if (base_n == 0)
		return (0);
	offset = ft_atoi_base_get_offset(str, base);
	negative = (offset < 0) ? -1 : 1;
	if (offset < 0)
		offset *= -1;
	if (ft_atoi_base_indexof(base, str[offset]) == -1)
		return (0);
	length = 0;
	while (str[offset + length] &&
	ft_atoi_base_indexof(base, str[offset + length]) != -1)
		length++;
	if (length == 0)
		return (0);
	return (negative * ft_atoi_base_get_result(
		str + offset, base, length, base_n));
}
