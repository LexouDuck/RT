/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:12 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 00:11:08 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(char const *str1, char const *str2)
{
	size_t	i;
	t_u8	c1;
	t_u8	c2;

	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = (t_u8)str1[i];
		c2 = (t_u8)str2[i];
		if (c1 != c2)
			return ((int)(c1 - c2));
		++i;
	}
	c1 = (t_u8)str1[i];
	c2 = (t_u8)str2[i];
	return ((int)(c1 - c2));
}
/*
**	if (str1 == str2)
**		return (0);
**	if (str1 && str2)
**	{
**
**	}
**	return ((str1 == NULL ? 0 : str1[0]) -
**			(str2 == NULL ? 0 : str2[0]));
*/
