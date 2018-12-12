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

# include "../../libft_memory.h"
# include "../../libft_convert.h"

char	*ft_s8_to_str(t_s8 number)
{
	char	*result;
	t_u8	digits[N8_MAXDIGIT];
	t_u8	i;
	t_s16	n;

	n = number;
	if (number < 0)
		n = -n;
	ft_memclr(digits, N8_MAXDIGIT);
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	n = 0;
	result[n++] = (number == 0) ? '0' : '-';
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}

char	*ft_s16_to_str(t_s16 number)
{
	char	*result;
	t_u8	digits[N16_MAXDIGIT];
	t_u8	i;
	t_s32	n;

	n = number;
	if (number < 0)
		n = -n;
	ft_memclr(digits, N16_MAXDIGIT);
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	n = 0;
	result[n++] = (number == 0) ? '0' : '-';
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}

char	*ft_s32_to_str(t_s32 number)
{
	char	*result;
	t_u8	digits[N32_MAXDIGIT];
	t_u8	i;
	t_s64	n;

	n = number;
	if (number < 0)
		n = -n;
	ft_memclr(digits, N32_MAXDIGIT);
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	n = 0;
	result[n++] = (number == 0) ? '0' : '-';
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}
