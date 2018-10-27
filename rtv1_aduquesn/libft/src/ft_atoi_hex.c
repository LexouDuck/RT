/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:41:59 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static inline int	ft_atoi_hex_ishexchar(char c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}

static inline int	ft_atoi_hex_getdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

int					ft_atoi_hex(const char *str)
{
	int		i;
	long	result;
	int		negative;

	i = 0;
	while (!(ft_atoi_hex_ishexchar(str[i]) || str[i] == '+' || str[i] == '-'))
		++i;
	negative = 0;
	if (str[i] == '-')
	{
		negative = 1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	else if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	result = 0;
	while (str[i] && ft_atoi_hex_ishexchar(str[i]))
		result = result * 16 + ft_atoi_hex_getdigit(str[i++]);
	return ((int)(negative ? -result : result));
}
