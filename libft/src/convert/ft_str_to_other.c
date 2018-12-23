/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_str_to_other.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_char.h"
#include "../../libft_convert.h"

t_bool	ft_str_to_bool(char const *str)
{
	size_t	i;

	i = 0;
	while (!(ft_isalpha(str[i])))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (FALSE);
		++i;
	}
	if (!str[i])
		return (FALSE);
	if ((str[i + 0] == 'T' || str[i + 0] == 't') ||
		(str[i + 1] == 'R' || str[i + 1] == 'r') ||
		(str[i + 2] == 'U' || str[i + 2] == 'u') ||
		(str[i + 3] == 'E' || str[i + 3] == 'e'))
		return (TRUE);
	else
		return (FALSE);
}

size_t	ft_str_to_size(char const *str)
{
	size_t	result;
	size_t	i;

	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		++i;
	}
	return (result);
}
