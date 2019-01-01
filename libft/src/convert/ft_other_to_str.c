/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_other_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"

char	*ft_bool_to_str(t_bool number)
{
	char	*result;

	if (number)
	{
		if (!(result = (char *)malloc(5)))
			return (NULL);
		result[0] = 'T';
		result[1] = 'R';
		result[2] = 'U';
		result[3] = 'E';
		result[4] = '\0';
	}
	else
	{
		if (!(result = (char *)malloc(6)))
			return (NULL);
		result[0] = 'F';
		result[1] = 'A';
		result[2] = 'L';
		result[3] = 'S';
		result[4] = 'E';
		result[5] = '\0';
	}
	return (result);
}

char	*ft_size_to_str(size_t number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64b];
	t_u8	i;
	size_t	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}
