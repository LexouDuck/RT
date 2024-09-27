/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:11 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:40:12 by Lexou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memsub(void const *ptr, size_t offset, size_t n)
{
	void	*result;
	size_t	i;

	if (ptr == NULL)
		return (NULL);
	result = malloc(n);
	i = 0;
	while (i < n)
	{
		((char *)result)[i] = ((char *)ptr)[offset + i];
	}
	return (result);
}
