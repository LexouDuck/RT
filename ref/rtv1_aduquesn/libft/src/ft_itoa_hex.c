/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:44:22 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_itoa_hex_get_string(
		unsigned int n,
		char const *prefix,
		int length)
{
	char	*result;
	char	*digits;
	int		i;

	digits = (char *)malloc(length + 8 + 2);
	i = 0;
	while (n > 0)
	{
		digits[i] = (n % 16);
		digits[i] += (digits[i] < 10) ? '0' : 'A' - 10;
		n /= 16;
		++i;
	}
	n = length;
	while (n--)
	{
		digits[i] = prefix[n];
		++i;
	}
	digits[i] = '\0';
	result = ft_strrev(digits);
	free(digits);
	return (result);
}

char		*ft_itoa_hex(
		unsigned int number,
		char const *prefix)
{
	char	*result;
	int		length;
	int		i;

	length = ft_strlen(prefix);
	if (number == 0)
	{
		result = (char *)malloc(length + 2);
		i = 0;
		while (i < length)
		{
			result[i] = prefix[i];
			++i;
		}
		result[i++] = '0';
		result[i] = '\0';
	}
	else
	{
		result = ft_itoa_hex_get_string(number, prefix, length);
	}
	return (result);
}
