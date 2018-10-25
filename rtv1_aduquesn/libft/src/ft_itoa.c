/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/15 02:08:09 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_itoa_get_string(int number)
{
	char	*result;
	char	*digits;
	long	n;
	int		i;

	i = 0;
	if (!(digits = (char *)malloc(10 + 2)))
		return (NULL);
	n = (number < 0) ? (long)number * -1 : (long)number;
	while (n > 0)
	{
		digits[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (number < 0)
		digits[i++] = '-';
	digits[i] = '\0';
	result = ft_strrev(digits);
	free(digits);
	return (result);
}

char		*ft_itoa(int number)
{
	char	*result;

	if (number == 0)
	{
		if (!(result = (char *)malloc(2)))
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		result = ft_itoa_get_string(number);
	}
	return (result);
}
