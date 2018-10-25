/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:14 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/18 19:23:04 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strnequ(char const *str1, char const *str2, size_t n)
{
	size_t i;

	if (str1 == str2 || n == 0)
		return (1);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i])
		{
			if (str1[i] != str2[i])
				return (0);
			++i;
			if (i == n)
				return (1);
		}
		return (str1[i] == str2[i]);
	}
	return (0);
}
