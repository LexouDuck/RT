/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_float_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"

char		*ft_f32_to_str(t_f32 number, t_u8 precision)
{
	char	*result;
	char	digits[32];
	t_u8	i;
	t_u64	n;

	i = 0;
	while (++i <= precision)
		number *= 10;
	n = (number < 0) ? -(t_u64)number : (t_u64)number;
	i = 0;
	while (n > 0 || i < precision)
	{
		digits[i++] = (n % 10) + '0';
		n /= 10;
		if (i == precision && (digits[i++] = '.'))
			if (n == 0 && number != 0)
				digits[i++] = '0';
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char		*ft_f64_to_str(t_f64 number, t_u8 precision)
{
	char	*result;
	char	digits[64];
	t_u8	i;
	t_u64	n;

	i = 0;
	while (++i <= precision)
		number *= 10;
	n = (number < 0) ? -(t_u64)number : (t_u64)number;
	i = 0;
	while (n > 0 || i < precision)
	{
		digits[i++] = (n % 10) + '0';
		n /= 10;
		if (i == precision && (digits[i++] = '.'))
			if (n == 0 && number != 0)
				digits[i++] = '0';
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}
