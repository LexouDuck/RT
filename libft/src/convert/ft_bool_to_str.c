/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_bool_to_str.c                           :+:      :+:    :+:   */
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
