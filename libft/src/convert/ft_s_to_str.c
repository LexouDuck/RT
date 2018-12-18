/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_s_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"

char	*ft_s8_to_str(t_s8 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_8b];
	t_u8	i;
	t_s16	n;

	n = number;
	if (number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = 1;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}

char	*ft_s16_to_str(t_s16 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_16b];
	t_u8	i;
	t_s32	n;

	n = number;
	if (number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = 1;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}

char	*ft_s32_to_str(t_s32 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_32b];
	t_u8	i;
	t_s64	n;

	n = number;
	if (number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = 1;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}

char	*ft_s64_to_str(t_s64 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64b];
	t_u8	i;
	t_u64	n;

	n = number;
	if (number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = 1;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}
