/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:13 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:14 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striter(char *str, void (*f)(char *))
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		f(str + i);
		++i;
	}
}
/*
**	if (str == NULL || f == NULL)
**		return ;
*/
