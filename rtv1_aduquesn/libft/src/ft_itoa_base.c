/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:09 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:39:27 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_itoa_base_check_base(char const *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i - 1;
		while (j >= 0)
		{
			if (base[i] == base[j])
				return (0);
			j--;
		}
		++i;
	}
	return (i < 2 ? 0 : i);
}

static char	*ft_itoa_base_get_string(int number, char const *base, int length)
{
	char	*result;
	char	*digits;
	long	n;
	int		i;

	i = 0;
	if (!(digits = (char *)malloc(32 + 2)))
		return (NULL);
	n = (number < 0) ? (long)number * -1 : (long)number;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (number < 0)
		digits[i++] = '-';
	digits[i] = '\0';
	result = ft_strrev(digits);
	free(digits);
	return (result);
}

char		*ft_itoa_base(int number, char const *base)
{
	char	*result;
	int		length;

	if (number == 0)
	{
		result = (char *)malloc(2);
		result[0] = base[0];
		result[1] = '\0';
		return (result);
	}
	length = ft_itoa_base_check_base(base);
	if (length == 0)
		return (NULL);
	result = ft_itoa_base_get_string(number, base, length);
	return (result);
}
