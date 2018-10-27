/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:09 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_ftoa_getstr(char *digits, float number, int precision, long n)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		digits[i++] = (n % 10) + '0';
		n /= 10;
		if (i == precision)
		{
			digits[i++] = '.';
			if (n == 0)
				digits[i++] = '0';
		}
	}
	while (i < precision)
		digits[i++] = '0';
	if (i == precision)
	{
		digits[i++] = '.';
		digits[i++] = '0';
	}
	if (number < 0)
		digits[i++] = '-';
	digits[i] = '\0';
}

char		*ft_ftoa(float number, int precision)
{
	char	*result;
	char	*digits;
	long	n;
	int		i;

	if (number == 0.0)
	{
		if (!(result = (char *)malloc(2)))
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		if (!(digits = (char *)malloc(32)))
			return (NULL);
		i = 0;
		while (++i <= precision)
			number *= 10;
		n = (number < 0) ? -(long)number : (long)number;
		ft_ftoa_getstr(digits, number, precision, n);
		result = ft_strrev(digits);
		free(digits);
	}
	return (result);
}
