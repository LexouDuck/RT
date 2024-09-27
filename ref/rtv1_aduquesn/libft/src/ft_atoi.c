/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:44:38 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		negative;

	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	negative = 0;
	if (str[i] == '-')
	{
		negative = 1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((int)(negative ? -result : result));
}
